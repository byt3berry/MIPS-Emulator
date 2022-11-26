// Projet MIPS 2022-2023
// Auteurs: Cocagne_Strainovic

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "..//include//fonctionModes.h"
#include "..//include//fonctionInstructions.h"
#include "..//include//fonctionFiles.h"
#include "..//include//utils.h"

int main(int argc, char **argv) {
    printf("Hello émulateur MIPS!\n");

    char chaine[15] = "abcdef1234";
    toUpperCase(chaine);
    printf("%s\n", chaine);

    int registres[32] = {0};

    // read(file, registres);

    switch (argc) {
        case 1:
            printf("Interactif\n");
            modeInteractif(registres);
            break;
        case 3:
            printf("Pas a pas\n");
            modeAutoPasAPas(argv[1], registres);
            break;
        case 4:
            printf("Auto\n");
            modeAuto(argv[1], argv[2], argv[3], registres);
            break;
        default:
            break;
    }

    printf("Bye émulateur MIPS!\n");

    return 0;
}
