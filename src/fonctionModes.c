#include <stdio.h>
#include <stdlib.h>

#ifndef _FONCTION_MODES_C_
#define _FONCTION_MODES_C_

#include "../include/fonctionModes.h"
#include "../include/fonctionFiles2.h"

#endif

void modeInteractif(int *registers) {
}

void modeAutoPasAPas(char *nomProgAssembleur, int *registers) {
    FILE *progAssembleur = fopen(nomProgAssembleur, "r");

    readPas(progAssembleur, registers);

    fclose(progAssembleur);
}

void modeAuto(char *nomProgAssembleur, char *nomFichierAssemble, char *nomFichierFinal, int *registers) {
    FILE *progAssembleur = fopen(nomProgAssembleur, "r");
    FILE *fichierAssemble = fopen(nomFichierAssemble, "w");
    FILE *fichierFinal = fopen(nomFichierFinal, "w");

    if (progAssembleur == NULL) {
        printf("Un des fichiers ne fonctionne pas\n");
        exit(1);
    }

    readAuto(progAssembleur, fichierAssemble, registers);

    fclose(progAssembleur);
    fclose(fichierAssemble);
    fclose(fichierFinal);
}
