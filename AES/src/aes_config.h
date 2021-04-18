//
// Created by Benedikt Kluss and Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_CONFIG_H
#define AES_CONFIG_H

/*------  General AES Specifications  -------*/
#define BYTES_IN_WORD 4
#define MESSAGE_SIZE_IN_WORDS 4
#define MESSAGE_BYTE_SIZE 16
#define ROUND_KEY_BYTE_SIZE 16

/* ------- 128bit Key-AES Specifications ----*/
#define NUMBER_OF_ROUNDS_128BIT_KEY 10
#define KEY_LENGTH_128BIT_BYTE_SIZE 16

/*------- 192bit Key-AES  Specifications ----*/
#define NUMBER_OF_ROUNDS_192BIT_KEY 12
#define KEY_LENGTH_192BIT_BYTE_SIZE 24

#endif