// Projet MIPS 2022-2023
// Auteurs: Cocagne_Strainovic

#include <stdio.h>
#include "fonctionModes.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

// TODO: implémenter la distinction entre les mnémoniques de registres et les registres
// TODO: ranger les fonctions dans des fichiers spécifiques
// TODO: verifier que les erreurs soient bien checkées pour le nouveau code
// TODO: implémenter immédiats en hex
// TODO: bug programme si un caractere n'est ni une lettre, ni un nombre, ni un $ ou une ,

int main(int argc, char **argv) {
//    unsigned int PC = 0b01010110011101100111001010010100;
//    unsigned int PCupper = 0b11110000000000000000000000000000;
//    unsigned int target = 0b10110001010001010001100010;
//    unsigned int result = (PC & PCupper) | (target << 2);
//
//    printf("PC      : %b\n", PC);
//    printf("PCupper : %b\n", PC & PCupper);
//    printf("terget  : %b\n", target);
//    printf("result  : %b\n", result);

//    char string[] = "Hello World!\0";
//    unsigned int len = strlen(string);
//    printf("%s : %d\n", string, len);

//    int x = 0b01111111111111111111111111111111;
//    int y = x + 1;
//    printf("%d : %b\n", x, x);
//    printf("%d : %b\n", y, y);

//    unsigned int PCupper = 0b11110000000000000000000000000000;  // pour recuperer les 4 bits de poids fort de PC
//    int PCupper2 = (int) PCupper;
//    printf("%b\n", PCupper);
//    printf("%b\n", PCupper2);

    /*
     * De 0 à 31 : les registres de 0 à 31
     * 32 : HI
     * 33 : LO
     * 34 : PC
     */
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
