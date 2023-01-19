// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#include "utils.h"

/*
 * It replaces all occurrences of a character in a string with another character
 * 
 * @param string the string to be modified
 * @param suppr the character to be replaced
 * @param add the character to add
 */
void replaceChar(char *string, const char suppr, const char add) {
    while (*string != '\0') {
        if (*string == suppr) {
            *string = add;
        }
        string++;
    }
}

void addChar(char *string, const int index, const char add) {
    char temp1 = add;
    char temp2;

    for(int i = 0; temp1 != '\0'; i++) {
        temp2 = string[index + i];
        string[index + i] = temp1;
        temp1 = temp2;
    }
}

/*
 * It takes a string and converts all lowercase letters to uppercase letters
 *
 * @param string The string to be converted to uppercase.
 */
void toUpperCase(char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if ('a' <= string[i] && string[i] <= 'z') {
            string[i] -= 32;
        }
    }
}

void toLowerCase(char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if ('A' <= string[i] && string[i] <= 'Z') {
            string[i] += 32;
        }
    }
}

long getLowerBits(const int nLowerBits) {
    int output = 0b0;
    int puissanceDe2 = 1;

    for (int i = 0; i < nLowerBits; i++) {
        output += puissanceDe2;
        puissanceDe2 *= 2;
    }

    return output;
}

long getUpperBits(const int nUpperBits, const int nTotalBits) {
    long output = getLowerBits(nUpperBits) << (nTotalBits - nUpperBits);

    return output;
}
