//
// Created by Hendrik on 08.01.2021.
//
#include <string.h>

#include "../src/decryption/decrypt_Decryption.c"
#include "../../decryption/src/decrypt_Services.c"
#include "../src/inverseSBox/inverseSBox.c"
#include "../../src/keyExpansion/keyExpansion.c"
#include "../../src/sBoxes/sBoxes.c"
#include "../../../lib/TestLibrary.c"

unsigned char message[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
unsigned char key128bit[] =     {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
unsigned char roundKeyRoundTen[] = { 0x13, 0x11, 0x1d, 0x7f, 0xe3, 0x94, 0x4a, 0x17, 0xf3, 0x07, 0xa7, 0x8b, 0x4d, 0x2b, 0x30, 0xc5};
unsigned char resultRoundTen[] = { 0x7a, 0xd5, 0xfd, 0xa7, 0x89, 0xef, 0x4e, 0x27, 0x2b, 0xca, 0x10, 0x0b, 0x3d, 0x9f, 0xf5, 0x9f};


int testWithSingleRoundKey(const unsigned char * cipheredMessage, unsigned char * roundKey, unsigned char * expectedResult){
    unsigned char * decipheredMessage = malloc(MESSAGE_BYTE_SIZE);
    strncpy(decipheredMessage, cipheredMessage, MESSAGE_BYTE_SIZE);
    int testFailed = 0;

    decipheredMessage = applyRoundKeyOnMessage(decipheredMessage, roundKey);
    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        testFailed += assertExpectedEqualsActual(expectedResult[i], decipheredMessage[i]);
    }

    if (!testFailed) {
        printf("SUCCESS: Test with Single Round Key.\n");
    } else {
        printf("FAILED: Test with Single Round Key.\n");
    }

    free(decipheredMessage);
    return testFailed;
}

int testWithExpandedKey(const unsigned char * cipheredMessage, unsigned char * key, int currentRound, unsigned char * expectedResult){
    unsigned char * expandedKey = getExpanded128bitKey(key);
    unsigned char * decipheredMessage = malloc(MESSAGE_BYTE_SIZE);
    strncpy(decipheredMessage, cipheredMessage, MESSAGE_BYTE_SIZE);
    int testFailed = 0;

    decipheredMessage = applyAddRoundKeyTransformation(decipheredMessage, expandedKey, currentRound);
    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        testFailed += assertExpectedEqualsActual(expectedResult[i], decipheredMessage[i]);
    }

    if (!testFailed) {
        printf("SUCCESS: Test with expanded Key.\n");
    } else {
        printf("FAILED: Test with expanded Key.\n");
    }

    free(decipheredMessage);
    free(expandedKey);
    return testFailed;
}


int main(){
    initializeAESDecryptionResources();

    int numberOfFailedTests = 0;

    numberOfFailedTests += testWithSingleRoundKey(message, roundKeyRoundTen, resultRoundTen);
    numberOfFailedTests += testWithExpandedKey(message, key128bit, 10, resultRoundTen);

    freeAESDecryptionResources();
    return numberOfFailedTests;
}