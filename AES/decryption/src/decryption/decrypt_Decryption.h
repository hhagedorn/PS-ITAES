//
// Created by Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#ifndef AES_DECRYPT_DECRYPTION_H
#define AES_DECRYPT_DECRYPTION_H

/* @param ciphered_message array of size 16
 * @param expanded_key array of size 176
 * @return pointer to ciphered_message now holding the deciphered_message
 * */
extern unsigned char * apply128bitDecryption(unsigned char * ciphered_message, unsigned char * expanded_key);

/* @param message_struct text size has to be multiple of 16
 * @param key array of size 16
 * @return pointer to ciphered_message now holding the deciphered_message
 * */
extern struct charText * apply128bitDecryptionOnText(struct charText * message_struct, unsigned char * key);

#endif //AES_DECRYPT_DECRYPTION_H
