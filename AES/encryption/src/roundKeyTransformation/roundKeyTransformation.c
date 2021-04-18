//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include "roundKeyTransformation.h"
#include "../../../src/aes_config.h"

void applyAddRoundKeyTransformation(struct resources * r, unsigned char round) {
    for (int byte_Position = 0; byte_Position < ROUND_KEY_BYTE_SIZE; ++byte_Position) {
           r->message[byte_Position] ^= r->expanded_key[byte_Position + (round * ROUND_KEY_BYTE_SIZE)];
        }
}