//
// Created by Benedikt Kluss on 24.01.21.
//
#include <stdlib.h>
#include <string.h>

#include "../../lib/TestLibrary.h"
#include "../src/hexConversions/hexConversions.h"

int main() {
    int result = 0;
    struct charText * test_text = malloc(sizeof(struct charText));
    unsigned char * text = calloc(32, 1);

    unsigned char hex_string[] = "00112233445566778899aabbccddeeff";
    memcpy(text, hex_string, 32);
    unsigned char hex_array[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

    test_text->text = text;
    test_text->text_length = 32;

    readFromHex(test_text);
    for (int i = 0; i < test_text->text_length ; ++i) {
        result += assertExpectedEqualsActual(hex_array[i], test_text->text[i]);
    }

    convertToHexString(test_text);
    for (int i = 0; i < test_text->text_length ; ++i) {
        result += assertExpectedEqualsActual(hex_string[i], test_text->text[i]);
    }

    return result;
}