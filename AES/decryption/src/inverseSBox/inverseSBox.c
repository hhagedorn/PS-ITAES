//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include <stdio.h>

#include "inverseSBox.h"

#include <stdlib.h>

#include "../decrypt_Services.h"

unsigned char * inv_sbox; // local variable containing a 256byte inverse SBox
int inverse_sbox_is_initialised = 0;

static unsigned char applyCircularBitShiftLeftOnByte(unsigned char byte, int shift_count) {
    return (byte << shift_count) | (byte >> (8 - shift_count));
}

/* Multiply inverse_element_of_galois_field by x + 1 ∈ GF(2^8) */
static unsigned char applyGaloisFieldMultiplicationByThree(unsigned char galois_value) {
    return galois_value ^ (galois_value << 1) ^ (galois_value & 0x80 ? 0x11B : 0);
}

/* Divide inverse_element_of_galois_field by x + 1 ∈ GF(2^8) */
static unsigned char applyGaloisFieldDivisionByThree(unsigned char galois_value) {
    galois_value ^= galois_value << 1;
    galois_value ^= galois_value << 2;
    galois_value ^= galois_value << 4;
    galois_value ^= galois_value & 0x80 ? 0x09 : 0;
    return galois_value;
}

static unsigned char * getMultiplicativeInverseLookupTable() {
    unsigned char * lookup_table = mallocUnsignedChar(INVERSE_SBOX_SIZE);

    unsigned char galoisfield_element = 1, galoisfield_inverse = 1;
    do {
        galoisfield_element = applyGaloisFieldMultiplicationByThree(galoisfield_element);
        galoisfield_inverse = applyGaloisFieldDivisionByThree(galoisfield_inverse);

        lookup_table[galoisfield_element] = galoisfield_inverse;
    } while (galoisfield_element != 1);

    lookup_table[0] = 0;

    return lookup_table;
}


static unsigned char * applyMappingToMultiplicativeInverse(unsigned char * bytes) {
    unsigned char * lookup_table = getMultiplicativeInverseLookupTable();

    for(int i = 0; i < INVERSE_SBOX_SIZE; ++i) {
        bytes[i] = lookup_table[bytes[i]];
    }

    free(lookup_table);
    return bytes;
}

static unsigned char * applyInverseAffineTransformation(unsigned char * bytes) {
    for(int i = 0; i < INVERSE_SBOX_SIZE; ++i) {
        bytes[i] = applyCircularBitShiftLeftOnByte(bytes[i], 1)
                   ^ applyCircularBitShiftLeftOnByte(bytes[i], 3)
                   ^ applyCircularBitShiftLeftOnByte(bytes[i], 6)
                   ^ 0x05;
    }
    return bytes;
}

/* Function described in associated Header */
unsigned char * getInverseSBox() {
    unsigned char * inverse_sbox = mallocUnsignedChar(INVERSE_SBOX_SIZE);
    for (int initial_value=0; initial_value < INVERSE_SBOX_SIZE; ++initial_value) {
        inverse_sbox[initial_value] = initial_value;
    }

    inverse_sbox = applyInverseAffineTransformation(inverse_sbox);
    inverse_sbox = applyMappingToMultiplicativeInverse(inverse_sbox);

    /* 0x00 has no inverse, set to 0x52 according to specification */
    inverse_sbox[0] = 0x52;

    return inverse_sbox;
}

static void initializeInverseSBox() {
    inv_sbox = getInverseSBox();
    inverse_sbox_is_initialised = 1;
}

void freeInverseSBox() {
    if (inverse_sbox_is_initialised) free(inv_sbox);
    inverse_sbox_is_initialised = 0;
}

unsigned char getInverseSubByteSubstituteFromSingleValue(unsigned char input) {
    if (!inverse_sbox_is_initialised) initializeInverseSBox();
    return inv_sbox[input];
}

/* Function described in associated Header */
unsigned char * getInverseSubByteSubstitutesFromArray(unsigned char * input, int input_array_length) {
    if (!inverse_sbox_is_initialised) initializeInverseSBox();
    for (int i = 0; i < input_array_length; ++i) {
        input[i] = inv_sbox[input[i]];
    }
    return input;
}