//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_RESOURCES_H
#define AES_RESOURCES_H

struct resources {
    unsigned char * sBox;
    unsigned char * message;
    unsigned char * expanded_key;
    unsigned int number_of_rounds;
};

struct resources * getResources(int aes_version);

void freeAllResources(struct resources * r);

#endif //AES_RESOURCES_H
