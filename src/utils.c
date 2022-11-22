#include "..//include//utils.h"

int areStringsEqual(char* mot1, char* mot2) {
    if ((int) *mot1 != (int) *mot2) {
        return 0;
    } else if ((int) *mot1 == 0 && (int) *mot2 == 0) {
        return 1;
    } else {
        mot1++;
        mot2++;
        return areStringsEqual(mot1, mot2);
    }
}

/*
int areStringsEqual(char* mot1, char* mot2) {
    while ((int) *mot1 || (int) *mot2) {
        if (*mot1 != *mot2) {
            return 0;
        }
        mot1++;
        mot2++;
    }

    return 1;
}
*/

void conversionBinaireHexa(char nombre_binaire[]){
    int nombre_hexadecimal[8] = {};
    int position = 0;
    char nombre_hex_affiche[8] = "";

    for(int i = 1; i <= 8; i++) {
		int nombre_stock = 0;
        for(int j = 4; j >= 1; j--) {
            position = (4*i)- j;

            nombre_stock += ((nombre_binaire[position])-'0') * pow(2, j-1);
        }

		nombre_hexadecimal[i-1] = nombre_stock;
    }

    for(int i = 0; i < 8; i++){
		switch(nombre_hexadecimal[i]){

            case 0:
                nombre_hex_affiche[i] = '0';
                break;

            case 1:
                nombre_hex_affiche[i] = '1';
                break;

            case 2:
                nombre_hex_affiche[i] = '2';
                break;

            case 3:
                nombre_hex_affiche[i] = '3';
                break;

            case 4:
                nombre_hex_affiche[i] = '4';
                break;

            case 5:
                nombre_hex_affiche[i] = '5';
                break;

            case 6:
                nombre_hex_affiche[i] = '6';
                break;

            case 7:
                nombre_hex_affiche[i] = '7';
                break;

            case 8:
                nombre_hex_affiche[i] = '8';
                break;

            case 9:
                nombre_hex_affiche[i] = '9';
                break;

            case 10:
                nombre_hex_affiche[i] = 'A';
                break;

            case 11:
                nombre_hex_affiche[i] = 'B';
                break;

            case 12:
                nombre_hex_affiche[i] = 'C';
                break;

            case 13:
                nombre_hex_affiche[i] = 'D';
                break;

            case 14:
                nombre_hex_affiche[i] = 'E';
                break;

            case 15:
                nombre_hex_affiche[i] = 'F';
                break;
            
            default:
                nombre_hex_affiche[i] = '!';
        }
    }

	printf("Le nombre hexadécimal est : %s\n", nombre_hex_affiche);
}

void conversionBinaireHexa2(char nombre_binaire[]){
    int nombre_hexadecimal[8] = {};
    int position = 0;
    char nombre_hex_affiche[8] = "";

    for(int i = 1; i <= 8; i++) {
		int nombre_stock = 0;
        for(int j = 4; j >= 1; j--) {
            position = (4*i)- j;

            nombre_stock += ((nombre_binaire[position])-'0') * pow(2, j-1);
        }

		nombre_hexadecimal[i-1] = nombre_stock;
    }

    for (int i=0; i < 8; i++) {
        sprintf(&nombre_hex_affiche[i], "%X", nombre_hexadecimal[i]);
    }

	printf("Le nombre hexadécimal est : %s\n", nombre_hex_affiche);
}