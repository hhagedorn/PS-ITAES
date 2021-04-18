//
// Created by Benedikt Kluss on 14.01.21.
//

#include "../../../lib/TestLibrary.h"
#include "../../src/aes_config.h"
#include "../src/mixedColumnsTransformation/mixedColumnsTransformation.h"
#include <stdlib.h>
#include <string.h>

int main()
{
    int result = 0;
    unsigned char * message = malloc(16);
    unsigned char tempMessage[] = {0x63, 0x53, 0xe0, 0x8c, 0x09, 0x60, 0xe1, 0x04, 0xcd, 0x70, 0xb7, 0x51, 0xba, 0xca, 0xd0, 0xe7};
    unsigned char expected[] = {0x5f, 0x72, 0x64, 0x15, 0x57, 0xf5, 0xbc, 0x92, 0xf7, 0xbe, 0x3b, 0x29, 0x1d, 0xb9, 0xf9, 0x1a};

    memcpy(message, tempMessage, MESSAGE_BYTE_SIZE);

    applyMixedColumnsTransformation(message);

    for (int i = 0; i < 16; ++i) {
        result += assertExpectedEqualsActual(expected[i] , message[i]);
    }

    free(message);

    return result;
}