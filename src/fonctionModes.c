#include <stdio.h>
#include <stdlib.h>

#ifndef _FONCTION_MODES_C_
#define _FONCTION_MODES_C_

#include "../include/fonctionModes.h"
#include "../include/fonctionFiles.h"

#endif

void modeInteractif(int *registres) {
}

void modeAutoPasAPas(char *nomProgAssembleur, int *registres) {
    FILE *progAssembleur = fopen(nomProgAssembleur, "r");

    readPas(progAssembleur, registres);

    fclose(progAssembleur);
}

void modeAuto(char *nomProgAssembleur, char *nomFichierAssemble, char *nomFichierFinal, int *registres) {
    FILE *progAssembleur = fopen(nomProgAssembleur, "r");
    FILE *fichierAssemble = fopen(nomFichierAssemble, "w");
    FILE *fichierFinal = fopen(nomFichierFinal, "w");

    if (progAssembleur == NULL || fichierAssemble == NULL || fichierFinal == NULL) {
        printf("Un des fichiers ne fonctionne pas\n");
        exit(1);
    }

    readAuto(progAssembleur, fichierAssemble, fichierFinal, registres);

    fclose(progAssembleur);
    fclose(fichierAssemble);
    fclose(fichierFinal);
}
