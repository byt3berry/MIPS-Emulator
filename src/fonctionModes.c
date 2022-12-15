#include <stdio.h>
#include <stdlib.h>

#ifndef FONCTION_MODES_C_
#define FONCTION_MODES_C_
#include "fonctionModes.h"
#include "read.h"
#endif

void modeInteractif(int *registers) {
    readInteractif(registers);
}

void modeAutoPasAPas(char *nomProgAssembleur, int *registers) {
    FILE *progAssembleur = fopen(nomProgAssembleur, "r");

    if (progAssembleur == NULL) {
        printf("Probleme avec le fichier source \"%s\"\n", nomProgAssembleur);
        exit(1);
    }

    readPas(progAssembleur, registers);

    fclose(progAssembleur);
}

void modeAuto(char *nomProgAssembleur, char *nomFichierAssemble, char *nomFichierFinal, int *registers) {
    FILE *progAssembleur = fopen(nomProgAssembleur, "r");
    FILE *fichierAssemble = fopen(nomFichierAssemble, "w");
    FILE *fichierFinal = fopen(nomFichierFinal, "w");

    if (progAssembleur == NULL) {
        printf("Probleme avec le fichier source \"%s\"\n", nomProgAssembleur);
        exit(1);
    }

    readAuto(progAssembleur, fichierAssemble, registers);

    fclose(progAssembleur);
    fclose(fichierAssemble);
    fclose(fichierFinal);
}
