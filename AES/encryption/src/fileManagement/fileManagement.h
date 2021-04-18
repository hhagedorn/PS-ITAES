//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#ifndef AES_FILEMANAGEMENT_H
#define AES_FILEMANAGEMENT_H

#include "../../../src/charText.h"

unsigned char * allocateInput(unsigned long length);

int exitProgramByFailure();

char * getUserInput();

char * getDefaultPath ();

char * getInputPath();

char * getOutputPath();

unsigned long getLengthOfFile (const char * file_path);

unsigned char * getTextFromInput(char * file_path, unsigned long text_length);

void saveEncryptedMessage(struct charText * encrypted_message, char * path);

#endif //AES_FILEMANAGEMENT_H
