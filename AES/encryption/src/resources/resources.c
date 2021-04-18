//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include <stdlib.h>

#include "resources.h"

#include "../../../src/sBoxes/sBoxes.h"
#include "../../../src/aes_config.h"

/*
 * aes_version = 128 at the moment
 */
struct resources * getResources(int aes_version) {
    struct resources * resources_pointer;
    resources_pointer = malloc(sizeof(struct resources));

    resources_pointer->message = calloc(MESSAGE_BYTE_SIZE, 1);
    resources_pointer->sBox = getSBox();
    resources_pointer->number_of_rounds = NUMBER_OF_ROUNDS_128BIT_KEY; //By default

    if (aes_version == 192) {
        resources_pointer->number_of_rounds = 12;
    }
    else if (aes_version == 256) {
        resources_pointer->number_of_rounds = 14;
    }

    return resources_pointer;
}

void freeAllResources (struct resources * r) {
    freeSBox();
    free(r->message);
    free(r->expanded_key);
    free(r);
}