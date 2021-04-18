//
// Created by Benedikt Kluss and Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_HEXCONVERSIONS_H
#define AES_HEXCONVERSIONS_H

#include "../charText.h"

extern struct charText * readFromHex(struct charText * hex_string);

extern struct charText * convertToHexString(struct charText * plain_text);

#endif //AES_HEXCONVERSIONS_H
