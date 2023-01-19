// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#include <stdio.h>
#include <stdlib.h>

#include "fonctionModes.h"
#include "read.h"


void modeInteractif() {
    readInteractif();
}

void modeAutoPasAPas(char *nomProgAssembleur) {
    FILE *progAssembleur = fopen(nomProgAssembleur, "r");

    if (progAssembleur == NULL) {
        printf("Probleme avec le fichier source \"%s\"\n", nomProgAssembleur);
        exit(1);
    }

    readPas(progAssembleur);

    fclose(progAssembleur);
}

void modeAuto(char *nomProgAssembleur, char *nomFichierAssemble, char *nomFichierFinal) {
    FILE *progAssembleur = fopen(nomProgAssembleur, "r");
    FILE *fichierAssemble = fopen(nomFichierAssemble, "w");
    FILE *fichierFinal = fopen(nomFichierFinal, "w");

    if (progAssembleur == NULL) {
        printf("Probleme avec le fichier source \"%s\"\n", nomProgAssembleur);
        exit(1);
    }

    readAuto(progAssembleur, fichierAssemble, fichierFinal);

    fclose(progAssembleur);
    fclose(fichierAssemble);
    fclose(fichierFinal);
}
