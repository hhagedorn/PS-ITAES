//
// Created by Hendrik on 12.01.2021.
//

#include "../src/decryption/decrypt_Decryption.c"
#include "../../decryption/src/decrypt_Services.c"
#include "../../decryption/src/inverseSBox/inverseSBox.c"
#include "../../src/keyExpansion/keyExpansion.c"
#include "../../src/sBoxes/sBoxes.c"
#include "../../../lib/TestLibrary.c"

unsigned char message[] = { 0x7a, 0xd5, 0xfd, 0xa7, 0x89, 0xef, 0x4e, 0x27, 0x2b, 0xca, 0x10, 0x0b, 0x3d, 0x9f, 0xf5, 0x9f};
unsigned char expectedOutcome[] = { 0x7a, 0x9f, 0x10, 0x27, 0x89, 0xd5, 0xf5, 0x0b, 0x2b, 0xef, 0xfd, 0x9f, 0x3d, 0xca, 0x4e, 0xa7};

int testInvShiftRows(unsigned char * cipheredMessage, unsigned char * expectedResult){
    unsigned char * actualResult = malloc(MESSAGE_BYTE_SIZE);
    strncpy(actualResult, cipheredMessage, MESSAGE_BYTE_SIZE);
    actualResult = applyInverseShiftRowsTransformation(actualResult);

    int testFailed = 0;
    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        testFailed += assertExpectedEqualsActual(expectedResult[i], actualResult[i]);
    }

    if (testFailed) {
        printf("FAILED: Testing InverseShiftRows() Transformation.\n");
    } else {
        printf("SUCCESS: Testing InverseShiftRows() Transformation.\n");
    }

    return testFailed;
}



int main(){
    initializeAESDecryptionResources();
    int numberOfFailedTests = 0;

    numberOfFailedTests += testInvShiftRows(message, expectedOutcome);

    freeAESDecryptionResources();
    return numberOfFailedTests;
}