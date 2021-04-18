//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "fileManagement.h"

#define MAX_USER_INPUT_LENGTH 32

static char default_directory[MAX_USER_INPUT_LENGTH] = "Files/";

int exitProgramByFailure() {
    for (int i = 10; i >= 0 ; --i) {
        printf("\rThe program will be shut down in %d seconds.", i);
        fflush(stdout);
        sleep(1);
    }
    exit(EXIT_FAILURE);
}

char * getUserInput() {
    char user_input[MAX_USER_INPUT_LENGTH];
    char * return_user_input = malloc(MAX_USER_INPUT_LENGTH);

    fgets(user_input, MAX_USER_INPUT_LENGTH, stdin);
    sscanf(user_input, "%s", return_user_input);
    fflush(stdin);

    return return_user_input;
}

static char * appendUserInputToDefaultDirectory(char * file_path) {
    char * return_directory = calloc(MAX_USER_INPUT_LENGTH, 1);

    memcpy(return_directory, default_directory, MAX_USER_INPUT_LENGTH);
    strcat(return_directory, file_path);

    free(file_path);

    return return_directory;
}

static char * getFilePath(char * file_path) {
    file_path = appendUserInputToDefaultDirectory(file_path);

    return file_path;
}

static int checkInputFileFound(char * file_path) {
    int file_found;
    FILE * file_pointer;
    file_pointer = fopen(file_path, "r");
    if (file_pointer == NULL) {
        printf("ERROR: File wasn't found.\n");
        exitProgramByFailure();
        file_found = 0;
    } else file_found = 1;

    fclose(file_pointer);

    return file_found;
}

char * getDefaultPath() {
    return default_directory;
}

char * getInputPath() {
    char * file_path = getUserInput();
    file_path = getFilePath(file_path);
    checkInputFileFound(file_path);

    return file_path;
}

char * getOutputPath() {
    char * default_output_filename = calloc(20, 1);
    char * default_file = "encryptedMessage.txt";
    sscanf(default_file, "%s", default_output_filename);

    char * file_path = getFilePath(default_output_filename);

    return file_path;
}

unsigned char * allocateInput(unsigned long length) {
    unsigned char * allocated_input = calloc(length, 1);

    if (allocated_input == NULL) {
        printf("ERROR: Memory allocation failed \n");
        exitProgramByFailure();
        return  0; //For clang tidy
    } else {
        return allocated_input;
    }
}

unsigned long getLengthOfFile(const char * file_path) {
    unsigned long text_length;
    FILE * file_pointer;

    file_pointer = fopen(file_path, "r");
    fseek(file_pointer, 0L, SEEK_END);
    text_length = ftell(file_pointer);

    fclose(file_pointer);
    return text_length;
}

static unsigned char * readInputFile(unsigned char * text_destination, char * file_path, unsigned long file_length) {
    FILE * file_pointer;

    file_pointer = fopen(file_path, "r");
    fread(text_destination, file_length, 1, file_pointer);
    fclose(file_pointer);

    free(file_path);
    return text_destination;
}

unsigned char * getTextFromInput(char * file_path, unsigned long text_length) {
    unsigned char * text_from_input = allocateInput(text_length);
    text_from_input = readInputFile(text_from_input, file_path, text_length);

    return text_from_input;
}

void saveEncryptedMessage(struct charText * encrypted_message, char * path) {
    FILE * file_pointer;

    file_pointer = fopen(path , "w" );
    fseek(file_pointer, 0, SEEK_END);
    fwrite(encrypted_message->text, encrypted_message->text_length, 1, file_pointer);

    fclose(file_pointer);
}