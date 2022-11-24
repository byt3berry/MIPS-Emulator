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

    // test

    int nombre = 10;
    char bin[6];
    decToBin5(nombre, bin);
    printf("%d : %s\n", nombre, bin);

    FILE *file = fopen("test.txt", "r");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return 1;
    }

    int registres[32] = {0};

    //read(file, registres);

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
