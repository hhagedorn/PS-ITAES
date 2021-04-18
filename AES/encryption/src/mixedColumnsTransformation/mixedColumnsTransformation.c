//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include <string.h>

#include "mixedColumnsTransformation.h"
#include "../../../src/aes_config.h"

//Multiplication designed for multiplication of 1,2,3
static unsigned char multiplicationInGaloisField(unsigned char number1, unsigned char  number2) {
    unsigned char result;

    if (number2 == 1) {
        result = number1;
    }
    else {
        result = (number1 << (number2 / 2))^ (number1 & 0x80 ? 0x1B : 0);
        if (number2 % 2 == 1) {
            result ^= number1; //To perform an odd multiplication
        }
    }
    return result;
}

void applyMixedColumnsTransformation(unsigned char * message) {
    unsigned char stored_word[4];
    unsigned char number1, number2;
    const unsigned char multiply_array[] = {
            0x02, 0x03, 0x01, 0x01,
            0x01, 0x02, 0x03, 0x01,
            0x01, 0x01, 0x02, 0x03,
            0x03, 0x01, 0x01, 0x02
    };

    for (int element_of_message = 0; element_of_message < MESSAGE_BYTE_SIZE; ++element_of_message) {
        if (element_of_message % MESSAGE_SIZE_IN_WORDS == 0) {
            memcpy(stored_word, message + element_of_message, BYTES_IN_WORD);
        }
        message[element_of_message] = 0;

        for (int row = 0; row < BYTES_IN_WORD; ++row) {
            number1 = stored_word[row];
            number2 = multiply_array[row + (element_of_message % BYTES_IN_WORD) * BYTES_IN_WORD];
            message[element_of_message] ^= multiplicationInGaloisField(number1, number2);
        }
    }
}