//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include <stdlib.h>

#include "sBoxes.h"

//Initialize the S-Box Array
unsigned char * sbox;
int sbox_is_initialized = 0;

//Performs a left circular shift
static unsigned char performCircularShiftLeft(unsigned char byte, unsigned char number_of_shifts){
    unsigned char right_bits = byte >> (8 - number_of_shifts);
    byte = right_bits + (byte << number_of_shifts);

    return byte;
}

//Performs the affine transformation in the galois field on a multiplicative inverse
static unsigned char performAffineTransformation(unsigned char multiplicative_inverse) {
    unsigned char affine_transformed_element = multiplicative_inverse;
    for (int shifts = 1; shifts <= 4 ; ++shifts) {
        affine_transformed_element ^= performCircularShiftLeft(multiplicative_inverse, shifts);
    }
    affine_transformed_element ^= 0x63;
    return affine_transformed_element;
}

/* Multiply galois_field_element by x + 1 ∈ GF(2^8) */
static unsigned char getNextElementOfGaloisFieldGenerator(unsigned char galois_field_element) {
    galois_field_element ^= (galois_field_element << 1) ^ (galois_field_element & 0x80 ? 0x1B : 0);
    return galois_field_element;
}

/* Divide galois_field_inverse by x + 1 ∈ GF(2^8) */
static unsigned char getNextInverseElementOfGaloisFieldGenerator(unsigned char galois_field_inverse) {
    galois_field_inverse ^= galois_field_inverse << 1;
    galois_field_inverse ^= galois_field_inverse << 2;
    galois_field_inverse ^= galois_field_inverse << 4;
    galois_field_inverse ^= galois_field_inverse & 0x80 ? 0x09 : 0;

    return galois_field_inverse;
}

void initializeAesSBox() {
    sbox = malloc(SIZE_OF_SBOX);
    unsigned char galois_field_element = 1, galois_field_inverse = 1;

    for (int i = 0; i < (SIZE_OF_SBOX / 2); ++i) {
        sbox[galois_field_element] = performAffineTransformation(galois_field_inverse);
        sbox[galois_field_inverse] = performAffineTransformation(galois_field_element);

        galois_field_element = getNextElementOfGaloisFieldGenerator(galois_field_element);
        galois_field_inverse = getNextInverseElementOfGaloisFieldGenerator(galois_field_inverse);
    }

    /* 0 is a special case since it has no inverse */
    sbox[0] = 0x63;

    sbox_is_initialized = 1;
}

/* Function described in associated header */
unsigned char * getSBox () {
    if(!sbox_is_initialized) initializeAesSBox();
    return sbox;
}

/* Function described in associated header */
void freeSBox(){
    if(sbox_is_initialized) free(sbox);
    sbox_is_initialized = 0;
}