//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include "encryptionAlgorithm.h"

#include "../shiftRowsTransformation/shiftRowsTransformation.h"
#include "../mixedColumnsTransformation/mixedColumnsTransformation.h"
#include "../roundKeyTransformation/roundKeyTransformation.h"
#include "../sBoxTransformation/sBoxTransformation.h"

struct resources * applyEncryptionAlgorithm(struct resources * aes_resources) {

    applyAddRoundKeyTransformation(aes_resources, 0);
    for (int round = 1; round <= aes_resources->number_of_rounds; ++round) {
        applySBoxTransformation(aes_resources);
        applyShiftRowsTransformation(aes_resources->message);
        if (round != aes_resources->number_of_rounds) {
            applyMixedColumnsTransformation(aes_resources->message);
        }
        applyAddRoundKeyTransformation(aes_resources, round);
    }

    return aes_resources;
}