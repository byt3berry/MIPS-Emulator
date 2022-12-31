// Projet MIPS 2022-2023
// Auteurs: Cocagne_Strainovic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctionModes.h"
#include "Instruction.h"
#include "utils.h"

// TODO: verifier que les erreurs soient bien checkées pour le nouveau code
// TODO: bug programme si un caractere n'est ni une lettre, ni un nombre, ni un $ ou une ,


int main(int argc, char **argv) {

    int x = 0b10011;
    printf("bin : %032b\n", x);
    printf("dec : %d\n", x);
    printf("hex : %08X\n", x);
    switch (argc) {
        case 1:
            printf("* * * * * * * * * * * * Mode Interactif * * * * * * * * * * * *\n\n");
            modeInteractif();
            break;
        case 3:
            printf("* * * * * * * * * * * *  Mode Pas a pas * * * * * * * * * * *\n");
            printf("Appuyez sur [ENTRER] pour passer à l'instruction suivante\n");
            printf("Appuyez sur n'importe quelle touche pour quitter l'émulateur\n\n");
            modeAutoPasAPas(argv[1]);
            break;
        case 4:
            printf("* * * * * * * * * * * * Mode Automatique * * * * * * * * * * * *\n\n");
            modeAuto(argv[1], argv[2], argv[3]);
            break;
        default:
            break;
    }

    printf("Bye émulateur MIPS!\n");

    return 0;
}
