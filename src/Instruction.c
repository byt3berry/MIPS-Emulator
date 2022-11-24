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

void setOutputR(Instruction *instruction, char *output) {
    int parametres[4];

    for (int i = 0; i < 4; i++) {
        if (instruction->parametresOrder[i] == 0) {
            parametres[i] = 0;
        } else {
            parametres[i] = instruction->parametres[i];
        }
    }

    char OPcode[6], func[6], x1[5], x2[5], x3[5], x4[5];
    decToBin(0, 6, OPcode);
    decToBin(parametres[0], 5, x1);
    decToBin(parametres[1], 5, x2);
    decToBin(parametres[2], 5, x3);
    decToBin(parametres[3], 5, x4);
    copyStrings(instruction->OPcodeOrFunc, func);

    sprintf(output, "%s%s%s%s%s%s", OPcode, x1, x2, x3, x4, func);
}

void setOutputI(Instruction *instruction, char *output) {
    int parametres[3];

    for (int i = 0; i < 3; i++) {
        if (instruction->parametresOrder[i] == 0) {
            parametres[i] = 0;
        } else {
            parametres[i] = instruction->parametres[i];
        }
    }

    char OPcode[6], x1[5], x2[5], x3[16];
    decToBin(0, 6, OPcode);
    decToBin(parametres[0], 5, x1);
    decToBin(parametres[1], 5, x2);
    decToBin(parametres[2], 16, x3);
    copyStrings(instruction->OPcodeOrFunc, OPcode);

    sprintf(output, "%s%s%s%s", OPcode, x1, x2, x3);
}

void setOutputJ(Instruction *instruction, char *output) {
    char OPcode[6], x[26];
    decToBin(instruction->parametres[0], 26, x);
    copyStrings(instruction->OPcodeOrFunc, OPcode);

    sprintf(output, "%s%s", OPcode, x);
}


void setOutputFull(Instruction *instruction, char *output) {

}