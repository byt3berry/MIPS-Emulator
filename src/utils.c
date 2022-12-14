#include "utils.h"
#include <string.h>
#include <stdlib.h>

/**
 * It converts a decimal number to a binary number
 * 
 * @param dec the decimal number to convert
 * @param nbBits the number of bits you want to convert to
 * @param bin the binary number
 */
void decToBin(int dec, int nbBits, char *bin) {
    int decAbs;
    if (dec < 0) {
        decAbs = -dec;
    } else {
        decAbs = dec;
    }
    
    char temp[nbBits];
    int i = 0;

    while (decAbs > 0 && i < nbBits) {
        temp[i] = decAbs % 2 + '0';
        decAbs /= 2;
        i++;
    }

    while (i < nbBits) {
        temp[i] = '0';
        i++;
    }

    for (int i = 0; i < nbBits; i++) {
        bin[i] = temp[nbBits - 1 - i];
    }

    bin[nbBits] = '\0';

    if (dec < 0) {
        complementA2(bin);
    }
}

/**
 * Calcul le complément à 2 d'un nombre binaire
 * 
 * @param nombre the string to be converted
 */
void complementA2(char *nombre) {
    int i = 0;

    while (nombre[i] != '\0'){i++;}  // on va a la fin de la chaine
    while (i >= 0 && nombre[i] != '1'){i--;} // on cherche le dernier 1

    i--;

    while (i >= 0) {
        nombre[i] = (nombre[i] == '1') ? '0' : '1';  // si on a un 1, ca devient un 0, sinon ca devient un 1
        i--;
    }
}

/**
 * It takes a string of binary digits and converts it to a string of hexadecimal digits
 * 
 * @param bin the binary string
 * @param hex the hexadecimal string
 */
void binToHex(char *bin, char *hex) {
    int temp[8];
    int position = 0;
    // char nombre_hex_affiche[8] = "";

    for (int i = 1; i <= 8; i++) {
        int nombre_stock = 0;
        for (int j = 4; j >= 1; j--) {
            position = (4 * i) - j;

            nombre_stock += ((bin[position]) - '0') * pow(2, j - 1);
        }

        temp[i - 1] = nombre_stock;
    }

    for (int i = 0; i < 8; i++) {
        sprintf(&hex[i], "%X", temp[i]);
    }
}

/**
 * It replaces all occurrences of a character in a string with another character
 * 
 * @param string the string to be modified
 * @param suppr the character to be replaced
 * @param add the character to add
 */
void replaceChar(char* string, char suppr, char add) {
    while(*string != '\0') {
        if (*string == suppr) {
            *string = add;
        }
        string++;
    }
}

/**
 * It removes all occurrences of a character from a string
 * 
 * @param string the string to remove the character from
 * @param suppr the character to be removed
 */
void removeChar(char *string, char suppr) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == suppr) {
            for (int j = i; string[j] != '\0'; j++) {
                string[j] = string[j+1];
            }
        }
    }
}


/**
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

