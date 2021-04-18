//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include "decrypt_Decryption.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../decrypt_Services.h"
#include "../inverseSBox/inverseSBox.h"
#include "../../../src/aes_config.h"
#include "../../../src/keyExpansion/keyExpansion.h"

static unsigned char * mixcolumns_multiplication_matrix;
static int mixcolumns_mult_matrix_is_initialised = 0;

static inline void printProgress(unsigned long goal_to_achieve, unsigned long current_progress) {
    unsigned long update_frequency_divisor = 102400; // multiple of MESSAGE_BYTE_SIZE
    if ((current_progress % update_frequency_divisor) == 0) {
        printf("\rProgress: %.0f %%.", 100*((double) current_progress  / (double) goal_to_achieve));
        fflush(stdout);
    }
}

static int rightMostBitOfByteEqualsOne(unsigned char input) {
    if (input & 0x01) return 1;
    return 0;
}

static int leftMostBitOfByteEqualsOne(unsigned char input) {
    if (input & 0x80) return 1;
    return 0;
}

static inline void copyTextBlockFromMessage (struct charText * message, unsigned char * destination_block, unsigned long message_block) {
    memcpy(destination_block, message->text + message_block, MESSAGE_BYTE_SIZE);
}

static inline void copyDecryptedBlockToMessage(unsigned char * input_block, struct charText * message, unsigned long message_block) {
    memcpy(message->text + message_block, input_block, MESSAGE_BYTE_SIZE);
}

static unsigned char * applyReverseOrderOnArray(unsigned char * byte_array, const int ARRAY_LENGTH) {
    unsigned char * reverse_byte_array = mallocUnsignedChar(ARRAY_LENGTH);

    for (int i = 0; i < ARRAY_LENGTH; ++i) {
        reverse_byte_array[i] = byte_array[ARRAY_LENGTH - (i + 1)];
    }

    byte_array = memcpy(byte_array, reverse_byte_array, ARRAY_LENGTH);
    free(reverse_byte_array);
    return byte_array;
}

static unsigned char * applyRotateArrayOnePositionRight(unsigned char * byte_array, const int ARRAY_LENGTH) {
    unsigned char rightmost_byte = byte_array[ARRAY_LENGTH - 1];

    for (int i = ARRAY_LENGTH - 1; i > 0; --i) {
        byte_array[i] = byte_array[i - 1];
    }
    byte_array[0] = rightmost_byte;

    return byte_array;
}

/* Function associated with getMixColumnsMultiplicativeMatrixFromPolynomial */
static unsigned char * fillRowOfMultiplicationMatrixWithPolynomial(unsigned char *multiplication_matrix, const unsigned char *polynomial, const int MAT_ROW) {
    for (int i = 0; i < 4; ++i) {
        multiplication_matrix[i + (4 * MAT_ROW)] = polynomial[i];
    }
    return multiplication_matrix;
}

/* Returns a 16 byte Array containing a Multiplication-Matrix for application of a four term
 * polynomial in the GF(2^8) Galois Field. */
static unsigned char * getMixColumnsMultiplicativeMatrixFromPolynomial(unsigned char *polynomial) {
    unsigned char * multiplication_matrix = mallocUnsignedChar(MESSAGE_BYTE_SIZE);

    polynomial = applyReverseOrderOnArray(polynomial, BYTES_IN_WORD);
    polynomial = applyRotateArrayOnePositionRight(polynomial, BYTES_IN_WORD);
    for (int matrix_row = 0; matrix_row < 4; ++matrix_row) {
        multiplication_matrix = fillRowOfMultiplicationMatrixWithPolynomial(multiplication_matrix, polynomial,
                                                                            matrix_row);
        polynomial= applyRotateArrayOnePositionRight(polynomial, BYTES_IN_WORD);
    }

    return multiplication_matrix;
}

/* Returns the multiplication matrix required to perform the InverseMixColumns() Transformation
 * as described in Sect. 5.3.3 of "Announcing the AES".*/
static unsigned char * getInverseMixColumnsMultiplicationMatrix() {
    if (!mixcolumns_mult_matrix_is_initialised) {
        unsigned char polynomial[] = {0x0e, 0x09, 0x0d, 0x0b};
        mixcolumns_multiplication_matrix = getMixColumnsMultiplicativeMatrixFromPolynomial(polynomial);
        mixcolumns_mult_matrix_is_initialised = 1;
    }
    return mixcolumns_multiplication_matrix;
}

/* Implementation of the Peasant's Algorithm to compute the product of
 * two factors in  Rijndael's Finite Field */
static unsigned char getGaloisFieldProduct(unsigned char factor1, unsigned char factor2) {
    unsigned char result = 0;

    int carry;
    for (int bit_in_factor = 0; bit_in_factor < 8; ++bit_in_factor) {
        if(rightMostBitOfByteEqualsOne(factor2)) {
            result ^= factor1;
        }
        factor2 = factor2 >> 1;
        carry = leftMostBitOfByteEqualsOne(factor1) ? 1 : 0;
        factor1 = factor1 << 1;
        if(carry) {
            factor1 ^= 0x1b;
        }
    }

    return result;
}

/* Function to obtain one element from MixColumns-Matrix-Multiplication with message.
 * @param message       message that will be multiplied according to MixColumns-Specification
 * @param RESULT_COLUMN column index of calculated result
 * @param RESULT_ROW    row index of calculated result
 * @return result       element in resultmatrix with position RESULT_COLUMN, RESULT_ROW
 * */
static unsigned char getResultElementOfMixColumnsMatrixMultiplication(const unsigned char * message, const int RESULT_COLUMN, const int RESULT_ROW) {
    unsigned char * multiplication_matrix = getInverseMixColumnsMultiplicationMatrix();
    unsigned char result = 0x00;

    for (int byte = 0; byte < BYTES_IN_WORD; ++byte) {
        result ^= getGaloisFieldProduct(multiplication_matrix[RESULT_ROW * 4 + byte], message[RESULT_COLUMN * 4 + byte]);
    }

    return result;
}

static unsigned char * applyRoundKeyOnMessage(unsigned char * message, const unsigned char * round_key) {
    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        message[i] ^= round_key[i];
    }
    return message;
}

static unsigned char * applyAddRoundKeyTransformation(unsigned char * message, const unsigned char * expanded_key, const int CURRENT_ROUND) {
    unsigned char * round_key = mallocUnsignedChar(ROUND_KEY_BYTE_SIZE);
    int position_of_round_key = CURRENT_ROUND * ROUND_KEY_BYTE_SIZE;

    memcpy(round_key, expanded_key + position_of_round_key, ROUND_KEY_BYTE_SIZE);
    message = applyRoundKeyOnMessage(message, round_key);

    free(round_key);
    return message;
}

static unsigned char * applyInverseShiftRowsTransformation(unsigned char * message) {
    unsigned char * result = mallocUnsignedChar(MESSAGE_BYTE_SIZE);
    int old_position_of_byte, new_position_of_byte;

    for (int row = 0; row < 4; ++row) {
        for (int byte_in_row = 0; byte_in_row < 4; ++byte_in_row) {
            old_position_of_byte = (byte_in_row * 4) + row;
            new_position_of_byte = (old_position_of_byte + (4 * row)) % 16;
            result[new_position_of_byte] = message[old_position_of_byte];
        }
    }

    free(message);
    message = result;
    return message;
}

static inline void freeInverseMixColumnsMultiplicationMatrix() {
    free(mixcolumns_multiplication_matrix);
    mixcolumns_mult_matrix_is_initialised = 0;
}

/* When no longer needed, the mult_matrix underlying the called Galois-Product
 * can be freed through function available above. */
static unsigned char * applyInverseMixColumnsTransformation(unsigned char * message) {
    unsigned char * result = mallocUnsignedChar(MESSAGE_BYTE_SIZE);

    for (int result_column = 0; result_column < 4; ++result_column) {
        for (int result_row = 0; result_row < 4; ++result_row) {
            result[result_row + result_column * 4] = getResultElementOfMixColumnsMatrixMultiplication(message,
                                                                                                      result_column,
                                                                                                      result_row);
        }
    }

    free(message);
    message = result;
    return message;
}

static unsigned char * applyInverseSubByteTransformation(unsigned char * message) {
    return getInverseSubByteSubstitutesFromArray(message, MESSAGE_BYTE_SIZE);
}

/* AES-Decryption of a ciphered Text, usable with either 128, 192 or 256 bit extended Keys. */
static unsigned char * applyDecryption(unsigned char * message, unsigned char * expanded_key, const int NUMBER_OF_ROUNDS) {
    int current_round = NUMBER_OF_ROUNDS;

    message = applyAddRoundKeyTransformation(message, expanded_key, current_round);
    for (--current_round; current_round >= 0 ; --current_round) {
        message = applyInverseSubByteTransformation(message);
        message = applyInverseShiftRowsTransformation(message);
        message = applyAddRoundKeyTransformation(message, expanded_key, current_round);
        if (current_round > 0 ) {
            message = applyInverseMixColumnsTransformation(message);
        }
    }

    freeInverseMixColumnsMultiplicationMatrix();
    return message;
}

unsigned char * apply128bitDecryption(unsigned char * ciphered_message, unsigned char * expanded_key) {
    return applyDecryption(ciphered_message, expanded_key, NUMBER_OF_ROUNDS_128BIT_KEY);
}

struct charText * apply128bitDecryptionOnText(struct charText * message_struct, unsigned char * key) {
    unsigned char * expanded_key = getExpanded128bitKey(key);
    unsigned char * temp_block = mallocUnsignedChar(MESSAGE_BYTE_SIZE);

    for (unsigned long current_message_block = 0; current_message_block < message_struct->text_length; current_message_block+=MESSAGE_BYTE_SIZE) {
        copyTextBlockFromMessage(message_struct, temp_block, current_message_block);
        temp_block = apply128bitDecryption(temp_block, expanded_key);

        copyDecryptedBlockToMessage(temp_block, message_struct, current_message_block);
        printProgress(message_struct->text_length, current_message_block);
    }

    free(temp_block);
    free(expanded_key);
    return message_struct;
}