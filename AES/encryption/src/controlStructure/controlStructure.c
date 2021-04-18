//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include <string.h>
#include <stdio.h>

#include "controlStructure.h"

#include "../input/inputHandling/inputHandling.h"
#include "../output/outputHandling/outputHandling.h"
#include "../encryptionAlgorithm/encryptionAlgorithm.h"
#include "../../../src/keyExpansion/keyExpansion.h"
#include "../../../src/aes_config.h"

static int hex_mode_enabled = 0;

static void setDecisionForHex() {
    int decision  = getDecisionOfHexModeFromUser();
    if(decision) {
        hex_mode_enabled = 1;
    }
    else {
        hex_mode_enabled = 0;
    }
}

int getHexMode() {
    return hex_mode_enabled;
}

static int freeAllAllocatedMemory(struct resources * r, struct charText * m, struct charText * k) {
    freeAllResources(r);
    freeAllInputResources(m);
    freeAllInputResources(k);

    return 0;
}

static struct charText * getKeyAccordingToVersionFromInput(int aes_version) {
    struct charText * key_struct = getKeyFromInput(KEY_LENGTH_128BIT_BYTE_SIZE); //default
    if (aes_version == 192) {
        getKeyFromInput(24); //Not fully implemented
    }
    else if (aes_version == 256) {
        getKeyFromInput(32); //Not fully implemented
    }

    return key_struct;
}

static void copyNextTextBlockToMessage (struct resources * aes_resources, struct charText * message_input, int message_block) {
    memcpy(aes_resources->message, message_input->text + message_block, MESSAGE_BYTE_SIZE);
}

static void copyEncryptedMessageBlockToText(struct charText * message, struct resources * aes_resources, int message_block) {
    memcpy(message->text + message_block, aes_resources->message, MESSAGE_BYTE_SIZE);
}

static void printProgress(unsigned long text_length, int text_block) {
    int progress_divisor_for_big_data = 102400;
    if ((text_block % progress_divisor_for_big_data) == 0) {
        printf("\rProgress: %.0f %%.", 100 * ((double)text_block / (double)text_length));
        fflush(stdout);
    }
}

struct charText * processAESControlStructure(struct resources * aes_resources, struct charText * text_to_encrypt, struct charText * key_input) {
    aes_resources->expanded_key=getExpanded128bitKey(key_input->text);

    for (int text_block = 0; text_block < text_to_encrypt->text_length; text_block += MESSAGE_BYTE_SIZE) {
        copyNextTextBlockToMessage(aes_resources, text_to_encrypt, text_block);
        applyEncryptionAlgorithm(aes_resources);

        copyEncryptedMessageBlockToText(text_to_encrypt, aes_resources, text_block);
        printProgress(text_to_encrypt->text_length, text_block);
    }

    return text_to_encrypt;
}

int startAESControlStructure(int aes_version) {
    setDecisionForHex();

    struct resources * aes_resources = getResources(aes_version);
    struct charText * text_to_encrypt = getPlainTextFromInput();
    struct charText * key_input = getKeyAccordingToVersionFromInput(aes_version);

    text_to_encrypt = processAESControlStructure(aes_resources, text_to_encrypt, key_input);

    safeGeneratedOutput(text_to_encrypt);
    freeAllAllocatedMemory(aes_resources, text_to_encrypt, key_input);

    return 0;
}