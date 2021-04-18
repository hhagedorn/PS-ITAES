//
// Created by Benedikt Kluss on 24.01.21.
//

#include <string.h>
#include <stdlib.h>

#include "../../../lib/TestLibrary.h"
#include "../src/controlStructure/controlStructure.h"

struct charText * initializeStructWithArray(unsigned char text[], int size) {
    struct charText * text_struct = malloc(sizeof (struct charText));
    text_struct->text = calloc(size, 1);
    text_struct->text_length = size;
    memcpy(text_struct->text, text, size);

    return text_struct;
}

int testOddInput() {
    int result = 0;
    int message_size = 31; //Has to be a divisor of 16 as the length of a input file gets expanded in inputHandling

    unsigned char expected[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a, 0x7c, 0x99, 0xf4, 0x2b, 0x6e, 0xe5, 0x03, 0x30, 0x9c, 0x6c, 0x1a, 0x67, 0xe9, 0x7a, 0xc2, 0x42};
    //Odd message of length 31
    unsigned char temp_message[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    unsigned char temp_key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    struct resources * aes_resources = getResources(128);
    struct charText * message_test = initializeStructWithArray(temp_message, message_size);
    struct charText * key_test =  initializeStructWithArray(temp_key, 16);

    message_test = processAESControlStructure(aes_resources, message_test, key_test);

    for (int i = 0; i <= message_size; ++i) {
        result += assertExpectedEqualsActual(expected[i], message_test->text[i]);
    }

    return result;
}

int testEmptyInput() {
    int result = 0;
    int message_size = 0;

    unsigned char * expected = calloc(message_size, 1);
    unsigned char * temp_message = calloc(message_size, 1);
    unsigned char temp_key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    struct resources * aes_resources = getResources(128);
    struct charText * message_test = initializeStructWithArray(temp_message, message_size);
    struct charText * key_test =  initializeStructWithArray(temp_key, message_size);

    message_test = processAESControlStructure(aes_resources, message_test, key_test);

    for (int i = 0; i < message_size; ++i) {
        result += assertExpectedEqualsActual(expected[i], message_test->text[i]);
    }
    return result;
}

int testLargerInputAs128() {
    int result = 0;
    int message_size = 32;

    unsigned char expected[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a, 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
    unsigned char temp_message[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
    unsigned char temp_key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    struct resources * aes_resources = getResources(128);
    struct charText * message_test = initializeStructWithArray(temp_message, message_size);
    struct charText * key_test =  initializeStructWithArray(temp_key, 16);

    message_test = processAESControlStructure(aes_resources, message_test, key_test);

    for (int i = 0; i < message_size; ++i) {
        result += assertExpectedEqualsActual(expected[i], message_test->text[i]);
    }

    return result;
}

int main () {
    int result = 0;

    result += testLargerInputAs128();
    result+= testEmptyInput();
    result+= testOddInput();

    return result;
}