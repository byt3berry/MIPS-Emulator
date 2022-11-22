#include <stdio.h>

#ifndef _FONCTION_MODES_C_
#define _FONCTION_MODES_C_
#include "../include/fonctionModes.h"
#endif

void modeInteractif(void){
}

void modeAutoPasAPas(char* nomProgAssembleur){
   FILE* progAssembleur = fopen(nomProgAssembleur, "r");
   fclose(progAssembleur);
}

void modeAuto(char* nomProgAssembleur, char* nomFichierAssemble, char* nomFichierFinal){
   FILE* progAsembleur = fopen(nomProgAssembleur, "r");
   FILE* fichierAssemble = fopen(nomFichierAssemble, "w");
   FILE* fichierFinal = fopen(nomFichierFinal, "w");
   fclose(progAsembleur);
   fclose(fichierAssemble);
   fclose(fichierFinal);
}