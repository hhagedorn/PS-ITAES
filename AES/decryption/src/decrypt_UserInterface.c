//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include "decrypt_UserInterface.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "decryption/decrypt_Decryption.h"
#include "decrypt_Services.h"
#include "fileManager/decrypt_FileManager.h"
#include "../../src/aes_config.h"
#include "../../src/charText.h"
#include "../../src/hexConversions/hexConversions.h"

static inline void setStdoutColourToRed() {
    printf("\033[0;31m");
}

static inline void setStdoutColourToGreen() {
    printf("\033[0;32m");
}

static inline void setStdoutColourToDefault() {
    printf("\033[0m");
}

static inline void printDecryptionComplete() {
    printf("\rProgress: 100 %%.");
    fflush(stdout);
    setStdoutColourToGreen();
    printf("...AES Decryption complete.\n\n");
    setStdoutColourToDefault();
}

static char * getUserInput() {
    char user_input[MAX_USER_INPUT_LENGTH];
    char * return_value = malloc(MAX_USER_INPUT_LENGTH);

    fgets(user_input, MAX_USER_INPUT_LENGTH, stdin);
    sscanf(user_input, "%s", return_value);

    return return_value;
}

static int getUserAgreement() {
    char * input = getUserInput();
    for (int i = 0; i < MAX_USER_INPUT_LENGTH; ++i) {
        if (input[i] == 'n') return 0;
    }
    return 1;
}

static int getUserDecisionIfInputIsHexadecimal() {
    printf("Is Input formatted as hexadecimal without any separators? [y/n]\n");
    if (getUserAgreement()) return 1;
    return 0;
}

static int getUserDecisionIfOutputShouldBeConvertedToHex() {
    printf("Should the output be stored in hexadecimal representation? [y/n]\n");
    if (getUserAgreement()) return 1;
    return 0;
}

static void startExitDialogue() {
    printf("\nProgram finished. Enter any character to exit.\n");
    getUserInput();

    exit(0);
}

static void startErrorExitDialogue() {
    setStdoutColourToRed();
    printf("\nAn ERROR occured. Program terminated. Enter any key to exit.\n");
    setStdoutColourToDefault();
    getUserInput();

    exit(EXIT_FAILURE);
}

static void startExitDecisionDialogue() {
    printf("Do you want to continue? [y/n]\n");
    if(!getUserAgreement()) exit(1);
}

/* Might return invalid path. To certainly obtain valid path use corresponding function below. */
static char * getDefaultDirectoryFilePathFromUser() {
    char * user_input = getUserInput();
    char files_path[50] = "Files/";

    strcat(files_path, user_input);
    memcpy(user_input, files_path, MAX_USER_INPUT_LENGTH);

    printf("Complete Filepath: %s\n", user_input);
    return user_input;
}

static char * getValidDefaultDirectoryPathFromUser() {
    char * file_path = getDefaultDirectoryFilePathFromUser();

    if(!filepathIsValid(file_path)) {
        printf("ERROR: File not Found! Filepath: %s", file_path);
        startErrorExitDialogue();
    }

    return file_path;
}

static char * getMessagePathDialogue() {
    printf("\nPlease enter name of textfile containing the ciphered message\n"
           "(only files in 'Files' Directory are considered):\n");
    return getValidDefaultDirectoryPathFromUser();
}

static char * getKeyPathDialogue() {
    printf("\nPlease enter path of textfile containing the decryption key:\n"
           "(only files in 'Files' Directory are considered):\n");
    return getValidDefaultDirectoryPathFromUser();
}

static struct charText * getMessageFromUser() {
    char * message_path = getMessagePathDialogue();
    struct charText * message = malloc(sizeof(struct charText));

    message->text_length = getLengthOfTextInFile(message_path);
    message->text = getBytesFromFile(message_path, message->text_length);

    printf("Retrieved Message of length %ld.\n", message->text_length);
    return message;
}

static struct charText * getKeyFromUser() {
    char * key_path = getKeyPathDialogue();
    struct charText * key = malloc(sizeof(struct charText));

    key->text_length = getLengthOfTextInFile(key_path);
    key->text = getBytesFromFile(key_path, key->text_length);

    return key;
}

static int messageIsOfCorrectSize(struct charText * message) {
    if (message->text_length % MESSAGE_BYTE_SIZE) {
        return 0;
    }
    return 1;
}

static int keyHasCorrectSize(struct charText * key, int expected_size) {
    if (key->text_length % expected_size) {
        return 0;
    }
    return 1;
}

static struct charText * cutMessageToCorrectSize(struct charText * message) {
    int appropriate_text_length = message->text_length - (message->text_length % MESSAGE_BYTE_SIZE);
    unsigned char * cut_text = mallocUnsignedChar(appropriate_text_length);
    printf("Actual length: %ld. Appropriate length: %d \n", message->text_length, appropriate_text_length);

    memcpy(cut_text, message->text, appropriate_text_length);
    free(message->text);
    message->text = cut_text;
    message->text_length = appropriate_text_length;

    printf("Cut off End of Message to result in new text length: %ld\n", message->text_length);
    return message;
}

static struct charText * cutKeyToCorrectSize(struct charText * key, int expected_size) {
    unsigned char * cut_text = mallocUnsignedChar(expected_size);
    printf("Actual length: %ld. Expected length: %d \n", key->text_length, expected_size);

    memcpy(cut_text, key->text, expected_size);
    free(key->text);
    key->text = cut_text;
    key->text_length = expected_size;

    printf("Cut off End of Key to result in new length: %ld\n", key->text_length);
    return key;
}

/* Conformed means converted from Hex if necessary and size being
 * ensured to be a multiple of MESSAGE_BYTE_SIZE. */
static struct charText * getConformedMessageFromUser() {
    struct charText * message = getMessageFromUser();

    if(getUserDecisionIfInputIsHexadecimal()) {
        message = readFromHex(message);
        printf("Hexadecimal message input enabled.\n");
    }

    if (!messageIsOfCorrectSize(message)) {
        printf("WARNING: Length of message not multiple of %d bytes.\n", MESSAGE_BYTE_SIZE);
        message = cutMessageToCorrectSize(message);
        startExitDecisionDialogue();
    }

    return message;
}

/* Conformed means converted from Hex if necessary and size being
 * ensured to be a multiple of MESSAGE_BYTE_SIZE. */
static struct charText * getConformed128bitKeyFromUser() {
    struct charText * key = getKeyFromUser();

    if(getUserDecisionIfInputIsHexadecimal()) {
        key = readFromHex(key);
        printf("Hexadecimal key input enabled.\n");
    }

    if (!keyHasCorrectSize(key, KEY_LENGTH_128BIT_BYTE_SIZE)) {
        if (key->text_length < KEY_LENGTH_128BIT_BYTE_SIZE) {
            printf("ERROR: Key too short. Expected size: %d. Actual size: %ld.", KEY_LENGTH_128BIT_BYTE_SIZE, key->text_length);
            startErrorExitDialogue();
        }

        printf("WARNING: Length of key exceeds expected length of %d bytes.\n", KEY_LENGTH_128BIT_BYTE_SIZE);
        key = cutKeyToCorrectSize(key, KEY_LENGTH_128BIT_BYTE_SIZE);
        startExitDecisionDialogue();
    }

    return key;
}

static void saveDecryptionResultToDefaultFile(struct charText * decrypted_message) {
    if (getUserDecisionIfOutputShouldBeConvertedToHex()) {
        decrypted_message = convertToHexString(decrypted_message);
        printf("Hexadecimal output enabled.\n");
    }

    char outputPath[] = "Files/decryptedMessage.txt";
    printf("Saving deciphered text to %s.\n", outputPath);
    saveToFile(decrypted_message, outputPath);
}

void runDecryptionViaUserInterface() {
    printf("128bit AES Decryption enabled.\n");
    struct charText * message = getConformedMessageFromUser();
    struct charText * key = getConformed128bitKeyFromUser();

    printf("\nBeginning AES Decryption...\n");
    message = apply128bitDecryptionOnText(message, key->text);

    printDecryptionComplete();
    saveDecryptionResultToDefaultFile(message);

    freeAllResourcesOfCharText(message);
    freeAllResourcesOfCharText(key);
    startExitDialogue();
}
