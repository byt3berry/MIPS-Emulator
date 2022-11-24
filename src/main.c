// Projet MIPS 2022-2023
// Auteurs: Cocagne_Strainovic

#include <stdio.h>
#include <math.h>
#include "..//include//fonctionModes.h"
#include "..//include//fonctionInstructions.h"
#include "..//include//fonctionFiles.h"
#include "..//include//utils.h"

int main(int argc, char **argv) {
    printf("Hello émulateur MIPS!\n");

    // int nombre = 0;
    // int nbBits = 5;
    // char bin[nbBits+1];
    // decToBin(nombre, nbBits, bin);
    // printf("%d : %s\n", nombre, bin);

    // int nombre = strtol("1101", NULL, 2);
    // int nombre2;
    // sscanf()
    // printf("%d\n", nombre);

    FILE *file = fopen("..//tests//arithmetic2.s", "r");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return 1;
    }

    int registres[32] = {0};

    read(file, registres);

    switch (argc) {
        case 1:
            modeInteractif();
            break;
        case 3:
            modeAutoPasAPas(argv[1]);
            break;
        case 4:
            modeAuto(argv[1], argv[2], argv[3]);
            break;
        default:
            break;
    }

    return 0;
}
