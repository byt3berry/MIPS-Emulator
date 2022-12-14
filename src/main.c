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
//    char strParameters[5][10] = {0};
//    char string[20] = "ADDI $5  $0 5";
//    int x = splitString(string, strParameters, ' ');
//    printf("%s : %s : %s : %s : %s : %d\n", strParameters[0], strParameters[1], strParameters[2], strParameters[3], strParameters[4], x);

//    char output1[20], output2[20], output3[20], output4[20];
//    sscanf("ok ok2,ok3,ok4", "%s %s , %s , %s", output1, output2, output3, output4);
//    printf("%s : %s : %s : %s\n", output1, output2, output3, output4);

    int registers[32] = {0};

    switch (argc) {
        case 1:
            printf("* * * * * * * * * * * * Mode Interactif * * * * * * * * * * * *\n\n");
            modeInteractif(registers);
            break;
        case 3:
            printf("* * * * * * * * * * * *  Mode Pas a pas * * * * * * * * * * *\n\n");
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
