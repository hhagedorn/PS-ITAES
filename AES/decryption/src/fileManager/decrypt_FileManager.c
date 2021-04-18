//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include "decrypt_FileManager.h"

#include <stdio.h>

#include "../decrypt_Services.h"

extern int filepathIsValid(const char * file_path){
    FILE * file;
    file = fopen(file_path, "r");
    if (file == NULL) {
        return 0;
    }
    return 1;
}

unsigned long getLengthOfTextInFile(const char * file_path) {
    unsigned long text_length;
    FILE * file;

    file = fopen(file_path, "r");
    fseek(file, 0L, SEEK_END);
    text_length = ftell(file);

    fclose(file);
    return text_length;
}

unsigned char * getBytesFromFile(const char * text_path, unsigned long text_size){
    unsigned char * text = mallocUnsignedChar(text_size);

    FILE * file_pointer;
    file_pointer = fopen(text_path, "r");
    fread(text, 1, text_size, file_pointer);

    fclose(file_pointer);
    return text;
}

void saveToFile(struct charText * text, char * file_path) {
    FILE * file;
    file = fopen(file_path, "w+");
    fwrite(text->text, 1, text->text_length, file);
    fclose(file);
}