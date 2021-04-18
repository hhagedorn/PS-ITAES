//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include <stdlib.h>
#include <string.h>

#include "inputHandling.h"

#include "../inputDialog/inputDialog.h"
#include "../../fileManagement/fileManagement.h"
#include "../../../../src/hexConversions/hexConversions.h"
#include "../../controlStructure/controlStructure.h"
#include "../../../../src/aes_config.h"

static unsigned long expandLengthToAesDivisor(unsigned long original_length_of_data, unsigned long length_of_aes_message) {
    unsigned long expanded_length, additional_length;

    if (original_length_of_data == 0) {
        expanded_length = 0;
    }
    else if ((original_length_of_data % length_of_aes_message) == 0) {
        expanded_length = original_length_of_data;
    }
    else {
        additional_length = (length_of_aes_message - (original_length_of_data % length_of_aes_message));
        expanded_length = original_length_of_data + additional_length;
    }

    return expanded_length;
}

static struct charText * copyExpandedTextToStruct(struct charText * input_data, unsigned char * expanded_text) {
    memcpy(expanded_text, input_data->text, input_data->text_length);
    free(input_data->text);
    input_data->text = expanded_text;

    return input_data;
}

static struct charText * expandPlainTextToAesDivisor(struct charText * input_data, unsigned long length_of_aes_message) {
    unsigned long expanded_length = expandLengthToAesDivisor(input_data->text_length, length_of_aes_message);
    unsigned char * expanded_text = allocateInput(expanded_length);

    input_data = copyExpandedTextToStruct(input_data, expanded_text);
    input_data->text_length = expanded_length;

    return input_data;
}

static struct charText * getCharTextStructWithInput (char * file_path) {
    struct charText * input_file = malloc(sizeof(struct charText));
    unsigned long original_length_of_data = getLengthOfFile(file_path);

    input_file->text_length = original_length_of_data;
    input_file->text = getTextFromInput(file_path, original_length_of_data);

    return input_file;
}

/*
 * Adjusted means that the size is expanded to an AES conform size and hexadecimal representation is applied if its wanted
 */
static struct charText * adjustCharTextToHexDecision(struct charText * input_data) {
    if (getHexMode()) {
        readFromHex(input_data);
    }

    return input_data;
}

int checkKeyLength(unsigned long key_size, int needed_length) {
    if(key_size != needed_length) {
        tellUserForWrongKeySize(needed_length);
        exitProgramByFailure();
        return 0; //For clang tidy
    }
    else return 1;
}

struct charText * getKeyFromInput(int length_of_key) {
    int adjusted_key_length = length_of_key + (getHexMode() * length_of_key);
    askUserForKeyPath(getDefaultPath(), adjusted_key_length);

    char * file_path = getInputPath();
    struct charText * key = getCharTextStructWithInput(file_path);
    checkKeyLength(key->text_length, adjusted_key_length);

    key = adjustCharTextToHexDecision(key);

    return key;
}

struct charText * getPlainTextFromInput() {
    askUserForPlainTextPath(getDefaultPath());
    char * file_path = getInputPath();
    struct charText * plain_text = getCharTextStructWithInput(file_path);

    plain_text = expandPlainTextToAesDivisor(plain_text, MESSAGE_BYTE_SIZE);
    plain_text = adjustCharTextToHexDecision(plain_text);

    return plain_text;
}

void freeAllInputResources(struct charText * input_resources) {
    free(input_resources->text);
    free(input_resources);
}

//Yes and No will be only accepted as Y and N or y and n
static int transformYesNoToBinary(char * input) {
    int decision;

    if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0) decision = 0;
    else if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) decision = 1;
    else  {
        free(input);
        return exitProgramByFailure();
    }

    return decision;
}

int getDecisionOfHexModeFromUser() {
    askUserForDecisionOfInputAsHex();

    char * input = getUserInput();
    int decision = transformYesNoToBinary(input);
    free(input);

    tellUserOfHexDecision(decision);
    return decision;
}