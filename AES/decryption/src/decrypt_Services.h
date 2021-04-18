//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_DECRYPT_SERVICES_H
#define AES_DECRYPT_SERVICES_H

#include "../../src/charText.h"

extern void freeAllResourcesOfCharText(struct charText * byte_text);

/* Prints a Warning and terminates program if memory allocation failed. */
extern unsigned char * mallocUnsignedChar(unsigned long BYTE_SIZE);

/* Initializes all AES-resources required independently of the
 * selected module to actually deploy the functionality.*/
extern void initializeAESDecryptionResources();

/* Frees all AES-resources required independently of the
 * selected module to actually deploy the functionality.*/
extern void freeAESDecryptionResources();

#endif