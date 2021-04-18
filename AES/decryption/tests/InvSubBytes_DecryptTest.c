//
// Created by Hendrik on 12.01.2021.
//

#include <string.h>

#include "../src/decryption/decrypt_Decryption.c"
#include "../../decryption/src/decrypt_Services.c"
#include "../src/inverseSBox/inverseSBox.c"
#include "../../src/keyExpansion/keyExpansion.c"
#include "../../src/sBoxes/sBoxes.c"
#include "../../../lib/TestLibrary.c"

unsigned char message[] = {0x7a, 0x9f, 0x10, 0x27, 0x89, 0xd5, 0xf5, 0x0b, 0x2b, 0xef, 0xfd, 0x9f, 0x3d, 0xca, 0x4e, 0xa7};
unsigned char expectedOutcome[] = {0xbd, 0x6e, 0x7c, 0x3d, 0xf2, 0xb5, 0x77, 0x9e, 0x0b, 0x61, 0x21, 0x6e, 0x8b, 0x10, 0xb6, 0x89};

int testInvSubBytes(const unsigned char * cipheredMessage, const unsigned char * expectedResult){
    unsigned char * actualResult = malloc(MESSAGE_BYTE_SIZE);
    strncpy(actualResult, cipheredMessage, MESSAGE_BYTE_SIZE);
    actualResult = applyInverseSubByteTransformation(actualResult);

    int testFailed = 0;
    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        testFailed += assertExpectedEqualsActual(expectedResult[i], actualResult[i]);
    }

    if (testFailed) {
        printf("FAILED: Testing InverseSubBytes() Transformation.\n");
    } else {
        printf("SUCCESS: Testing InverseSubBytes() Transformation.\n");
    }

    return testFailed;
}


int main() {
    initializeAESDecryptionResources();
    int numberOfFailedTests = 0;

    numberOfFailedTests += testInvSubBytes(message, expectedOutcome);

    freeAESDecryptionResources();
    return numberOfFailedTests;
}