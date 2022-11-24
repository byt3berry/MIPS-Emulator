#include <stdio.h>

#include "../include/Instruction.h"
#include "../include/utils.h"
#include "constantes.c"

void printInfos(Instruction *instruction) {
    printf("operateur     : %s\n", instruction->operateur);
    printf("format        : %d\n", instruction->format);
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

void setFormat(Instruction *instruction, int format) {
    instruction->format = format;
}

void setOPcodeOrFunc(Instruction *instruction, char *OPcodeOrFunc) {
    instruction->OPcodeOrFunc = OPcodeOrFunc;
}

void setNbParametres(Instruction *instruction, int nbParametres) {
    instruction->nbParametres = nbParametres;
}

void setParametres(Instruction *instruction, int *parametres) {
    // instruction->parametres[instruction->nbParametres] = registre;
    // instruction->nbParametres++;

//    instruction->parametre1 = x1;
//    instruction->parametre2 = x2;
//    instruction->parametre3 = x3;
//    instruction->parametre4 = x4;
    for (int i = 0; i < 4; i++) {
        if (i < instruction->nbParametres) {
            instruction->parametres[i] = parametres[i];
        } else {
            instruction->parametres[i] = 0;
        }
    }
}

int isNext(Instruction *instruction) {
    if (areStringsEqual(instruction->OPcodeOrFunc, "NOP\0") || areStringsEqual(instruction->OPcodeOrFunc, "SYSCALL\0")) {
        return 0;
    }
    return 1;
}