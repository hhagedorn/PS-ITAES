//
// Created by Benedikt Kluss on 06.01.21.
//
#include "TestLibrary.h"

int assertExpectedEqualsActual(unsigned char expected, unsigned char actual) {
    if (expected == actual) {
        return 0;
    } else {
        return 1;
    }
}

