//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include "shiftRowsTransformation.h"
#include "../../../src/aes_config.h"

/*
 * Takes message as input and handles as an matrix with size: dimension x dimension.
 * Matrix is build column-wise.
 * Shifts start on the 2nd row.
 */
void applyShiftRowsTransformation(unsigned char * message) {
    int dimension = BYTES_IN_WORD;
    unsigned char origin_positions[dimension], copied_row[dimension];
    unsigned char position_of_new_value;

    for (int row = 1; row < dimension; ++row) {
        //Copies Row
        for (int element_in_row = 0; element_in_row < dimension; ++element_in_row) {
            origin_positions[element_in_row] = row + element_in_row * dimension;
            copied_row[element_in_row] = message[origin_positions[element_in_row]];
        }
        //Shifts Row
        for (int element_in_row = 0; element_in_row < dimension; ++element_in_row) {
            position_of_new_value = (element_in_row + row) % dimension;
            message[origin_positions[element_in_row]] = copied_row[position_of_new_value];
        }
    }
}