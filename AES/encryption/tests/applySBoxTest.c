//
// Created by Benedikt Kluss on 18.01.21.
//
#include <string.h>

#include "../../../lib/TestLibrary.h"
#include "../src/sBoxTransformation/sBoxTransformation.h"
#include "../../src/aes_config.h"

int main() {
    int result = 0;

    unsigned char message[] = { 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0 };
    unsigned char expected[] = { 0x63, 0xca, 0xb7, 0x04, 0x09, 0x53, 0xd0, 0x51, 0xcd, 0x60, 0xe0, 0xe7, 0xba, 0x70, 0xe1, 0x8c};

    struct resources * aes_resources = getResources(128);
    memcpy(aes_resources->message, message, MESSAGE_BYTE_SIZE);

    applySBoxTransformation(aes_resources);

    for (int i = 0; i < MESSAGE_BYTE_SIZE; ++i) {
        result += assertExpectedEqualsActual(expected[i] , aes_resources->message[i]);
    }
    freeAllResources(aes_resources);

    return result;
}