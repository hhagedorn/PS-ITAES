//
// Created by Benedikt Kluss on 18.01.21.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#include "../src/encryptionAlgorithm/encryptionAlgorithm.h"
#include "../../../lib/TestLibrary.h"
#include "../src/encryptionAlgorithm/encryptionAlgorithm.h"
#include "../../src/keyExpansion/keyExpansion.h"
#include "../../src/sBoxes/sBoxes.h"
#include "../src/resources/resources.h"
#include "../../src/aes_config.h"

int main()
{
    int result = 0;
    unsigned char message[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
    unsigned char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    unsigned char expected[] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};

    struct resources * aes_resources = getResources(128);

    memcpy(aes_resources->message, message, MESSAGE_BYTE_SIZE);
    aes_resources->expanded_key =  getExpanded128bitKey(key);
    aes_resources->sBox = getSBox();

    aes_resources = applyEncryptionAlgorithm(aes_resources);

    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        result += assertExpectedEqualsActual(expected[i] , aes_resources->message[i]);
    }

   freeAllResources(aes_resources);

    return result;
}