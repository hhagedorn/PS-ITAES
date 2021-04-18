//
// Created by Benedikt Kluss.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//
#include "outputHandling.h"
#include "../outputDialog/outputDialog.h"
#include "../../fileManagement/fileManagement.h"
#include "../../../../src/hexConversions/hexConversions.h"
#include "../../controlStructure/controlStructure.h"

void safeGeneratedOutput(struct charText * encrypted_text) {
    char * output_path = getOutputPath();

    if (getHexMode()) {
        encrypted_text = convertToHexString(encrypted_text);
    }
    saveEncryptedMessage(encrypted_text, output_path);
    doOutputDialogWithUser(output_path);
    getUserInput();
}
