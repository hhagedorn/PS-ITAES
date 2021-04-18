//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include "decrypt_Services.h"
#include "decrypt_UserInterface.h"

/*----------------------MAIN----------------------- */
int main() {
    initializeAESDecryptionResources();

    runDecryptionViaUserInterface();

    freeAESDecryptionResources();
    return 0;
}

