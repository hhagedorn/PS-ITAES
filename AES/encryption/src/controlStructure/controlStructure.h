//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_CONTROLSTRUCTURE_H
#define AES_CONTROLSTRUCTURE_H

#include "../resources/resources.h"
#include "../../../src/charText.h"

/*
 * Starts the user dialogs and AES and therefore splits input_text into 128Bit blocks.
 */
int startAESControlStructure(int aes_version);

struct charText *  processAESControlStructure(struct resources * aes_resources, struct charText * text_to_encrypt, struct charText * key_input);

int getHexMode();

#endif //AES_CONTROLSTRUCTURE_H
