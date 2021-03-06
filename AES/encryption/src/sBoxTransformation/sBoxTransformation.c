//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include "sBoxTransformation.h"
#include "../../../src/aes_config.h"

void applySBoxTransformation(struct resources * r) {
    for (int byte_Position = 0; byte_Position < MESSAGE_BYTE_SIZE; ++byte_Position) {
        r->message[byte_Position] = r->sBox[r->message[byte_Position]];
    }
}