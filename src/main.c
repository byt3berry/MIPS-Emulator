// Projet MIPS 2022-2023
// Auteurs: Cocagne_Strainovic

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "..//include//fonctionModes.h"
#include "..//include//fonctionInstructions.h"
#include "..//include//fonctionFiles2.h"
#include "..//include//utils.h"

int main(int argc, char **argv) {
    printf("Hello émulateur MIPS!\n");

    // char string[8] = "Bonjour\0";
    // char ch = 'o';

    // for (int i = 0; string[i] != '\0'; i++) {
    //     if (string[i] == ch) {
    //         string[i] = ' ';
    //     }
    // }

    // int x = -5;
    // char output[6];
    // decToBin(x, 5, output);
    // printf("%d : %s\n", x, output);

    // char instr[8], x1[4], x2[4], x3[4];

    // sscanf("ADDI $5 5($6)", "%s $%s %s($%s)", instr, x1, x2, x3);

    // printf("%s %s %s %s\n", instr, x1, x2, x3);

    int registers[32] = {0};

    // read(file, registers);

    switch (argc) {
        case 1:
            printf("* * * * * * * * * * * * Mode Automatique * * * * * * * * * * * *\n\n");
            modeInteractif(registers);
            break;
        case 3:
            printf("* * * * * * * * * * * *  Mode Pas a pas * * * * * * * * * * *\n\n");
            modeAutoPasAPas(argv[1], registers);
            break;
        case 4:
            printf("* * * * * * * * * * * * Mode Interactif * * * * * * * * * * * *\n\n");
            modeAuto(argv[1], argv[2], argv[3], registers);
            break;
        default:
            break;
    }

    printf("Bye émulateur MIPS!\n");

    return 0;
}
