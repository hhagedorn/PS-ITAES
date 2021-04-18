///
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#ifndef AES_INPUTDIALOG_H
#define AES_INPUTDIALOG_H

void askUserForPlainTextPath(char * default_path);

void askUserForKeyPath(char * default_path, int length_of_key);

void tellUserForWrongKeySize(int needed_length);

void askUserForDecisionOfInputAsHex ();

void tellUserOfHexDecision (int decisionForHex);

#endif //AES_INPUTDIALOG_H
