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

/**
 * It takes a string, an index, and a character, and inserts the character at the index
 * 
 * @param string The string to add the character to.
 * @param index The index of the string where you want to add the character.
 * @param add The character to add to the string.
 */
void addChar(char *string, const int index, const char add) {
    char temp1 = add;
    char temp2;

    for(int i = 0; temp1 != '\0'; i++) {
        temp2 = string[index + i];
        string[index + i] = temp1;
        temp1 = temp2;
    }
}

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

/**
 * It returns a number with the first nLowerBits bits set to 1
 * 
 * @param nLowerBits the number of bits you want to get from the lower part of the number
 * 
 * @return the binary representation of the number of lower bits.
 */
long getLowerBits(const int nLowerBits) {
    int output = 0;
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
