//
// Created by Benedikt Kluss and Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../aes_config.h"
#include "../sBoxes/sBoxes.h"

static unsigned char current_rcon_value;

static void initializeRCONValue() {
    current_rcon_value = 0x01;
}

static void incrementRCONValue() {
    if (current_rcon_value < 0x80) {
        current_rcon_value = current_rcon_value << 1;
    } else
        current_rcon_value = (current_rcon_value << 1) ^ 0X1B;
}

static unsigned char * applyRotateWordLeftTransformation(unsigned char * word) {
    unsigned char first_word = word[0];

    for (int i = 0; i < BYTES_IN_WORD - 1; ++i) {
        word[i] = word[i + 1];
    }
    word[3] = first_word;

    return word;
}

static unsigned char * applySubByteTransformation(unsigned char * word) {
    unsigned char * sbox = getSBox();

    for(int i=0; i < BYTES_IN_WORD; ++i) {
        word[i] = sbox[word[i]];
    }

    return word;
}

static unsigned char * applyRCONTransformation(unsigned char * word) {
    word[0] = word[0] ^ current_rcon_value;
    incrementRCONValue();
    return word;
}

static unsigned char * applyTransformations(unsigned char * word) {
    word = applyRotateWordLeftTransformation(word);
    word = applySubByteTransformation(word);
    word = applyRCONTransformation(word);

    return word;
}

static unsigned char * fillInNextWord(unsigned char * expanded_key, int key_length_in_bytes, int word_position) {
    int begin_previous_word, begin_word_in_previous_key;
    unsigned char * temp_word = malloc(BYTES_IN_WORD);

    begin_previous_word = word_position - BYTES_IN_WORD;
    memcpy(temp_word, expanded_key + begin_previous_word, BYTES_IN_WORD);
    if (word_position % key_length_in_bytes == 0) {
        temp_word = applyTransformations(temp_word);
    }

    // generate new word according to new_word = temp_word XOR word_in_previous_key
    begin_word_in_previous_key = word_position - key_length_in_bytes;
    for (int byte = 0; byte < BYTES_IN_WORD; ++byte) {
        expanded_key[word_position + byte] = expanded_key[begin_word_in_previous_key + byte] ^ temp_word[byte];
    }

    free(temp_word);
    return expanded_key;
}


static unsigned char * createExpandedKey(const unsigned char * key, int key_length_in_bytes, int number_of_aes_rounds) {
    const unsigned int BYTES_IN_EXPANDED_KEY = key_length_in_bytes * (number_of_aes_rounds + 1);
    unsigned char * expanded_key = malloc(BYTES_IN_EXPANDED_KEY);
    initializeRCONValue();

    memcpy(expanded_key, key, key_length_in_bytes);
    for (int word = key_length_in_bytes; word < BYTES_IN_EXPANDED_KEY; word += BYTES_IN_WORD) {
        expanded_key = fillInNextWord(expanded_key, key_length_in_bytes, word);
    }

    return expanded_key;
}

unsigned char * getExpanded128bitKey(unsigned char *key) {
    unsigned char * expanded_key = createExpandedKey(key, KEY_LENGTH_128BIT_BYTE_SIZE, NUMBER_OF_ROUNDS_128BIT_KEY);
    return expanded_key;
}
