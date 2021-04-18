//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_INPUTHANDLING_H
#define AES_INPUTHANDLING_H

struct charText * getPlainTextFromInput();

struct charText * getKeyFromInput(int length_of_key);

void freeAllInputResources(struct charText * input_resources);

int getDecisionOfHexModeFromUser();

#endif //AES_INPUTHANDLING_H
