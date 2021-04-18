//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_SBOXES_H
#define AES_SBOXES_H

/* Size of SBox which is 16*16=256 */
#define SIZE_OF_SBOX 256

extern unsigned char * getSBox ();

extern void freeSBox();

#endif //AES_SBOXES_H
