//
// Created by Benedikt Kluss and Hendrik Hagedorn.
// Submitted on 5th of February 2021 as part of the project seminar "Implementing the AES",
// held at the Research Group for Cyber Security, WWU Muenster.
//

#include <stdlib.h>

#include "hexConversions.h"

static struct charText * setNewText(struct charText * char_text, unsigned char * new_text, unsigned long new_text_length) {
    free(char_text->text);
    char_text->text = new_text;
    char_text->text_length = new_text_length;

    return char_text;
}

static unsigned char get4bitHexValueFromChar(unsigned char input_char) {
    unsigned char hex_number;

    unsigned char minimum_number_of_hex = '0';
    unsigned char maximum_number_of_hex = '9';
    unsigned char minimum_letter_of_hex = 'a';

    if (input_char >= minimum_number_of_hex && input_char <= maximum_number_of_hex) {
        hex_number = input_char - minimum_number_of_hex;
    } else {
        hex_number = input_char - minimum_letter_of_hex + 10;
    }

    return hex_number;
}

static unsigned char getCharFrom4bitHexValue(unsigned char input_hex) {
    unsigned char char_value;

    unsigned char minimum_number_of_hex = '0';
    unsigned char minimum_letter_of_hex = 'a';

    if (input_hex >= 0 && input_hex <= 9) {
        char_value = input_hex + minimum_number_of_hex;
    } else {
        char_value = input_hex + minimum_letter_of_hex - 10;
    }

    return char_value;
}

struct charText * readFromHex(struct charText * hex_string) {
    unsigned long new_text_length = (hex_string->text_length + 1) / 2; // +1 for odd length
    unsigned char * result = calloc(new_text_length, 1);
    unsigned char current_char, hex_value, first_hex_digit, second_hex_digit;

    for(unsigned long i = 0; i < hex_string->text_length; i += 2) {
        current_char = hex_string->text[i];

        if (hex_string->text_length - i == 1 ) { // case last character in odd length
            hex_value = get4bitHexValueFromChar(current_char);
        } else {
            first_hex_digit = get4bitHexValueFromChar(current_char) * 16;
            second_hex_digit = get4bitHexValueFromChar(hex_string->text[i + 1]);
            hex_value = first_hex_digit ^ second_hex_digit;
        }

        result[(i / 2)] = hex_value;
    }
    setNewText(hex_string, result, new_text_length);

    return hex_string;
}

struct charText * convertToHexString(struct charText * plain_text) {
    unsigned long new_text_length = plain_text->text_length * 2;
    unsigned char * result = malloc(new_text_length);

    unsigned char first_half_hex, second_half_hex;
    int position_in_result;
    for (int i = 0; i < plain_text->text_length; ++i) {
        first_half_hex = plain_text->text[i] >> 4;
        second_half_hex = plain_text->text[i] & 0x0F;

        position_in_result = i*2;
        result[position_in_result] = getCharFrom4bitHexValue(first_half_hex);
        result[position_in_result + 1] = getCharFrom4bitHexValue(second_half_hex);
    }

    setNewText(plain_text, result, new_text_length);

    return plain_text;
}