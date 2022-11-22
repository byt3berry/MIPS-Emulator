#include <stdio.h>

#include "../include/Instruction.h"
#include "../include/utils.h"
#include "constantes.c"


void printInfos(Instruction* instruction) {
    printf("operateur     : %s\n", instruction->operateur);
    printf("format        : %d\n", instruction->format);
    printf("OPcodeOrFunc  : %s\n", instruction->OPcodeOrFunc);
    printf("nbParametres  : %d\n", instruction->nbParametres);
    printf("x1            : %d\n", (instruction->parametres)[0]);
    printf("x2            : %d\n", (instruction->parametres)[1]);
    printf("x3            : %d\n", (instruction->parametres)[2]);
}

void setOperateur(Instruction* instruction, char* operateur) {
    instruction->operateur = operateur;
}

void setFormat(Instruction* instruction, int format) {
    instruction->format = format;
    // switch (format) {
    //     case FORMAT_R:
    //         instruction->format = "R\0";
    //         break;
    //     case FORMAT_I:
    //         instruction->format = "I\0";
    //         break;
    //     case FORMAT_J:
    //         instruction->format = "J\0";
    //         break;
    // }
}

void setOPcodeOrFunc(Instruction* instruction, char* OPcodeOrFunc) {
    instruction->OPcodeOrFunc = OPcodeOrFunc;
}

void setParametres(Instruction* instruction, int registre) {
    if (instruction->nbParametres == NULL) {
        instruction->nbParametres = 0;
    }
    instruction->parametres[instruction->nbParametres] = registre;
    instruction->nbParametres++;
}

int isNext(Instruction* instruction) {
    if (areStringsEqual(instruction->OPcodeOrFunc, "NOP\0") || areStringsEqual(instruction->OPcodeOrFunc, "SYSCALL\0")) {
        return 0;
    }
    return 1;
}