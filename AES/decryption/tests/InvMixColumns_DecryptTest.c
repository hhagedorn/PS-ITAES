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

unsigned char message[] = { 0xba, 0xa0, 0x3d, 0xe7, 0xa1, 0xf9, 0xb5, 0x6e, 0xd5, 0x51, 0x2c, 0xba, 0x5f, 0x41, 0x4d, 0x23};
unsigned char expectedOutcome[] = { 0x3e, 0x1c, 0x22, 0xc0, 0xb6, 0xfc, 0xbf, 0x76, 0x8d, 0xa8, 0x50, 0x67, 0xf6, 0x17, 0x04, 0x95};

int testInvMixColumns(unsigned char * cipheredMessage, unsigned char * expectedResult){
    unsigned char * actualResult = malloc(MESSAGE_BYTE_SIZE);
    strncpy(actualResult, cipheredMessage, MESSAGE_BYTE_SIZE);
    actualResult = applyInverseMixColumnsTransformation(actualResult);

    int testFailed = 0;
    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        testFailed += assertExpectedEqualsActual(expectedResult[i], actualResult[i]);
    }

    if (testFailed) {
        printf("FAILED: Testing InverseMixColumns Transformation.\n");
    } else {
        printf("SUCCESS: Testing InverseMixColumns Transformation.\n");
    }

    return testFailed;
}



int main(){
    initializeAESDecryptionResources();
    int numberOfFailedTests = 0;

    numberOfFailedTests += testInvMixColumns(message, expectedOutcome);

    freeAESDecryptionResources();
    return numberOfFailedTests;
}