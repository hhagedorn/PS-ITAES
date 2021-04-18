//
// Created by Hendrik on 12.01.2021.
//

#include "../src/decryption/decrypt_Decryption.c"
#include "../../decryption/src/decrypt_Services.c"
#include "../src/inverseSBox/inverseSBox.c"
#include "../../src/keyExpansion/keyExpansion.c"
#include "../../src/sBoxes/sBoxes.c"

#include "../../../lib/TestLibrary.c"

int test128bitKeyDecryption(unsigned char * cipheredMessage, unsigned char * key, unsigned char * expectedResult){
    unsigned char * actualResult = malloc(MESSAGE_BYTE_SIZE);
    strncpy(actualResult, cipheredMessage, MESSAGE_BYTE_SIZE);
    actualResult = apply128bitDecryption(actualResult, key);

    int testFailed = 0;
    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        testFailed += assertExpectedEqualsActual(expectedResult[i], actualResult[i]);
    }

    if (testFailed) {
        printf("FAILED: Testing Decryption with 128bit Key.\n");
    } else {
        printf("SUCCESS: Testing Decryption with 128bit Key.\n");
    }

    return testFailed;
}

int test128bitKeyDecryptionOnText(unsigned char * cipheredMessage, unsigned char * key, unsigned char * expectedResult ) {
    struct charText * ciphered_text = malloc(sizeof(struct charText));
    ciphered_text->text_length = 32;
    ciphered_text->text = cipheredMessage;

    ciphered_text = apply128bitDecryptionOnText(ciphered_text, key);

    int testFailed = 0;
    for (int i = 0; i < 32; ++i) {
        testFailed += assertExpectedEqualsActual(expectedResult[i], ciphered_text->text[i]);
    }

    if (testFailed) {
        printf("\nFAILED: Testing Decryption of Textblocks with 128bit Key.\n");
    } else {
        printf("\nSUCCESS: Testing Decryption of Textblocks with 128bit Key.\n");
    }

    return testFailed;
}


int main(){
    initializeAESDecryptionResources();
    int numberOfFailedTests = 0;

    unsigned char message[] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
    unsigned char longmessage[] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a, 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
    unsigned char key[] =  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    unsigned char expectedOutcome[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    unsigned char longExpectedOutcome[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

    unsigned char * expandedKey = getExpanded128bitKey(key);

    numberOfFailedTests += test128bitKeyDecryption(message, expandedKey, expectedOutcome);
    numberOfFailedTests += test128bitKeyDecryptionOnText(longmessage, key, longExpectedOutcome);


    free(expandedKey);
    freeAESDecryptionResources();
    return numberOfFailedTests;
}