//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_INVERSESBOX_H
#define AES_INVERSESBOX_H

#define INVERSE_SBOX_SIZE 256

/* Returns pointer to allocated memory, containing the inverse Substitution-Table (SBox)
 * for the InverseSubBytes() Transformation.
 * The substitutes for any given input are stored in the Table position of the value.
 * (InverseSBox[value] provides the substitute).
 * Alternatively Substitutes can also be obtained by directly using the provided functions. */
unsigned char * getInverseSBox();

/* Can be used to transform a single byte by substitution in Rijndael's inverse SBox.
 * Reuses a once-only initialised inverse sbox. Once no more substitutes
 * are needed, the underlying table can be freed by calling the respective function. */
unsigned char getInverseSubByteSubstituteFromSingleValue(unsigned char input);

/* Can be used to transform an array of bytes by substitution in Rijndael's inverse SBox.
 * Reuses a once-only initialised inverse sbox. Once no more substitutes
 * are needed, the underlying table can be freed by calling the respective function. */
unsigned char * getInverseSubByteSubstitutesFromArray(unsigned char * input, int inputArrayLength);

/* Frees the memory allocated to the static variable storing the SBox*/
void freeInverseSBox();

#endif //AES_INVERSESBOX_H
