#include <stdio.h>

#include "../include/Instruction.h"
#include "../include/utils.h"
#include "constantes.c"

void printInfos(Instruction *instruction) {
    printf("operateur     : %s\n", instruction->operateur);
    printf("formatInput   : %d\n", instruction->formatInput);
    printf("formatOutput  : %d\n", instruction->formatOutput);
    printf("OPcodeOrFunc  : %s\n", instruction->OPcodeOrFunc);
    printf("nbParametres  : %d\n", instruction->nbParametres);
    printf("x1            : %d\n", instruction->parametres[0]);
    printf("x2            : %d\n", instruction->parametres[1]);
    printf("x3            : %d\n", instruction->parametres[2]);
    printf("x4            : %d\n", instruction->parametres[3]);
}

void setOperateur(Instruction *instruction, char *operateur) {
    instruction->operateur = operateur;
}

void setFormat(Instruction *instruction, int formatInput) {
    instruction->formatInput = formatInput;
}

void setOPcodeOrFunc(Instruction *instruction, char *OPcodeOrFunc) {
    instruction->OPcodeOrFunc = OPcodeOrFunc;
}

void setNbParametres(Instruction *instruction, int nbParametres) {
    instruction->nbParametres = nbParametres;
}

void setParametres(Instruction *instruction, int *parametres) {
    for (int i = 0; i < 4; i++) {
        if (i < instruction->nbParametres) {
            instruction->parametres[i] = parametres[i];
        } else {
            instruction->parametres[i] = 0;
        }
    }
}

void setParametresOrder(Instruction *instruction, int *parametresOrder){
    

    for (int i = 0; i < 4; i++) {
        instruction->parametresOrder[i] = parametresOrder[i];
    }
}
