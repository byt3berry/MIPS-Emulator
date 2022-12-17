// Projet MIPS 2022-2023
// Auteurs: Cocagne_Strainovic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "ExecuteFunctions.h"
#include "fonctionModes.h"
#include "Instruction.h"
#include "utils.h"

// TODO: verifier que les erreurs soient bien checkées pour le nouveau code
// TODO: bug programme si un caractere n'est ni une lettre, ni un nombre, ni un $ ou une ,


int main(int argc, char **argv) {
    /*
    unsigned int PC = 0b01010110011101100111001010010100;
    unsigned int PCupper = 0b11110000000000000000000000000000;
    unsigned int target = 0b10110001010001010001100010;
    unsigned int result = (PC & PCupper) | (target << 2);

    printf("PC      : %b\n", PC);
    printf("PCupper : %b\n", PC & PCupper);
    printf("terget  : %b\n", target);
    printf("result  : %b\n", result);

    char string[] = "Hello World!\0";
    unsigned int len = strlen(string);
    printf("%s : %d\n", string, len);

    int x = 0b01111111111111111111111111111111;
    int y = x + 1;
    printf("%d : %b\n", x, x);
    printf("%d : %b\n", y, y);

    unsigned int PCupper = 0b11110000000000000000000000000000;  // pour recuperer les 4 bits de poids fort de PC
    int PCupper2 = (int) PCupper;
    printf("%b\n", PCupper);
    printf("%b\n", PCupper2);

    for (int x3 = 0; x3 <= 5; x3++) {
        int param1 = 0b10010;
        int param2 = x3 % 5; // une rotation de 32 + n bits équivaut à une rotation de n bits
        int upperNbits = param1 & (int) getUpperBits(5 - param2, 5);
        int lowerNbits = param1 & (int) getLowerBits(param2);
        int upperNbitsShifted = upperNbits >> param2;
        param1 = lowerNbits << (5 - param2);

        printf("%b : %b\n", param1, param1 | upperNbitsShifted);
    }
*/
    /*
     * De 0 à 31 : les registres de 0 à 31
     * 32 : HI
     * 33 : LO
     * 34 : PC
     */

//    initExecuteFunctions();
    int registers[35] = {0};

    switch (argc) {
        case 1:
            printf("* * * * * * * * * * * * Mode Interactif * * * * * * * * * * * *\n\n");
            modeInteractif(registers);
            break;
        case 3:
            printf("* * * * * * * * * * * *  Mode Pas a pas * * * * * * * * * * *\n");
            printf("Appuyez sur [ENTRER] pour passer à l'instruction suivante\n");
            printf("Appuyez sur n'importe quelle touche pour quitter l'émulateur\n\n");
            modeAutoPasAPas(argv[1], registers);
            break;
        case 4:
            printf("* * * * * * * * * * * * Mode Automatique * * * * * * * * * * * *\n\n");
            modeAuto(argv[1], argv[2], argv[3], registers);
            break;
        default:
            break;
    }

    printf("Bye émulateur MIPS!\n");

    return 0;
}
