//
// Created by Benedikt Kluss on 12.01.21.
//
#include <stdlib.h>
#include <string.h>

#include "../../../lib/TestLibrary.h"
#include "../src/shiftRowsTransformation/shiftRowsTransformation.h"

int main()
{
    int result = 0;
    unsigned char * message = malloc(16);
    unsigned char tempMessage[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    memcpy(message, tempMessage, 16);

    unsigned char expected[] = {0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11};

    applyShiftRowsTransformation(message);

    for (int i = 0; i < 16; ++i) {
        result += assertExpectedEqualsActual(expected[i] , message[i]);
    }

    free(message);

    return result;
}