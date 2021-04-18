//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include <stdio.h>

#include "inputDialog.h"

void askUserForDecisionOfInputAsHex () {
    printf("Is message and key formatted as a hexadecimal without any separators? [y/n]\n");
}

void tellUserOfHexDecision (int decisionForHex) {
    printf("Hexadecimal mode is ");
    if (decisionForHex) {
        printf("\033[0;32m"); //change to color green
        printf("enabled");
    }
    else {
        printf("\033[0;31m");//change to color red
        printf("disabled");
    }
    printf("\033[0m");//change to default color
    printf("!\n");
}

void askUserForPlainTextPath(char * default_path) {
    printf("Please enter the filename of the message you want to encrypt in the %s directory:\n", default_path);
}

void askUserForKeyPath(char * default_path, int length_of_key) {
    printf("Please enter the filename containing the %d Byte long key you want to use to encrypt from the %s directory:\n", length_of_key, default_path);
}

void tellUserForWrongKeySize(int needed_length) {
    printf("ERROR: Key has not the size of of AES version you have called. Please use a key of length %d byte.\n", needed_length);
}
