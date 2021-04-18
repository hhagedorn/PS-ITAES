//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include "decrypt_Services.h"

#include <stdlib.h>
#include <stdio.h>

#include "../../src/sBoxes/sBoxes.h"
#include "../../src/charText.h"
#include "inverseSBox/inverseSBox.h"

void freeAllResourcesOfCharText(struct charText * byte_text) {
    free(byte_text->text);
    free(byte_text);
}

unsigned char * mallocUnsignedChar(const unsigned long BYTE_SIZE) {
    unsigned char * reserved_memory = malloc(BYTE_SIZE);

    if (reserved_memory == NULL) {
        printf("\n!!! Memory allocation failed !!!\n");
        exit(EXIT_FAILURE);
    }
    return reserved_memory;
}

void initializeAESDecryptionResources() {
    printf("Initialization of AES-Decryption complete.\n");
}

void freeAESDecryptionResources() {
    freeSBox();
    freeInverseSBox();

    printf("\nFreeing of AES-Decryption Resources finished.\n");
}

