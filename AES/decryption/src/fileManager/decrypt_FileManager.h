//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_DECRYPT_FILEMANAGER_H
#define AES_DECRYPT_FILEMANAGER_H

#include "../../../src/charText.h"

extern int filepathIsValid(const char * file_path);

extern unsigned long getLengthOfTextInFile(const char * file_path);

extern void saveToFile(struct charText * text, char * file_path);

extern unsigned char * getBytesFromFile(const char * text_path, unsigned long text_size);

#endif //AES_DECRYPT_FILEMANAGER_H
