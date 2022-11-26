#include <stdio.h>
#include <string.h>

#include "../include/Instruction.h"
#include "../include/utils.h"
#include "constantes.c"

// void initInstruction(Instruction *instruction) {
//     strcpy(instruction->operateur, "\0");
//     instruction->format = -1;
//     instruction->OPcodeOrFunc = -1;
//     instruction->nbParametres = -1;
//     instruction->parametres = {0};
//     instruction->parametresOrder = {0};
// }

void printInfos(Instruction *instruction) {
    printf("operateur     : %s\n", instruction->operateur);
    printf("format        : %d\n", instruction->format);
    printf("OPcodeOrFunc  : %d\n", instruction->OPcodeOrFunc);
    printf("nbParametres  : %d\n", instruction->nbParametres);
    printf("Ordre         : %d %d %d %d\n", instruction->parametresOrder[0], instruction->parametresOrder[1], instruction->parametresOrder[2], instruction->parametresOrder[3]);
    printf("x1            : %d\n", instruction->parametres[0]);
    printf("x2            : %d\n", instruction->parametres[1]);
    printf("x3            : %d\n", instruction->parametres[2]);
    printf("x4            : %d\n", instruction->parametres[3]);
}

void setOperateur(Instruction *instruction, char *operateur) {
    strcpy(instruction->operateur, operateur);
}

void setFormat(Instruction *instruction, int format) {
    instruction->format = format;
}

void setOPcodeOrFunc(Instruction *instruction, int OPcodeOrFunc) {
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

void setParametresOrder(Instruction *instruction, int *parametresOrder) {
    for (int i = 0; i < 4; i++) {
        instruction->parametresOrder[i] = parametresOrder[i];
    }
}

void setOutputR(Instruction *instruction, char *output) {
    int parametres[4];

    for (int i = 0; i < 4; i++) {
        int index = instruction->parametresOrder[i];
        if (index == 0) {
            parametres[i] = 0;
        } else {
            parametres[i] = instruction->parametres[index - 1];
        }
    }

    char OPcode[7], func[7], x1[6], x2[6], x3[6], x4[6];

    decToBin(0, 6, OPcode);
    decToBin(instruction->OPcodeOrFunc, 6, func);
    decToBin(parametres[0], 5, x1);
    decToBin(parametres[1], 5, x2);
    decToBin(parametres[2], 5, x3);
    decToBin(parametres[3], 5, x4);

    sprintf(output, "%s%s%s%s%s%s", OPcode, x1, x2, x3, x4, func);
}

void setOutputI(Instruction *instruction, char *output) {
    int parametres[3];

    for (int i = 0; i < 3; i++) {
        int index = instruction->parametresOrder[i];
        if (index == 0) {
            parametres[i] = 0;
        } else if (index == -1) {
            parametres[i] = 1;
        } else {
            parametres[i] = instruction->parametres[index - 1];
        }
    }

    char OPcode[7], x1[6], x2[6], x3[17];
    decToBin(instruction->OPcodeOrFunc, 6, OPcode);
    decToBin(parametres[0], 5, x1);
    decToBin(parametres[1], 5, x2);
    decToBin(parametres[2], 16, x3);

    // printf("%s\n", x1);
    // printf("%s\n", x2);
    // printf("%s\n", x3);


    sprintf(output, "%s%s%s%s", OPcode, x1, x2, x3);
}

void setOutputJ(Instruction *instruction, char *output) {
    char OPcode[7], x[27];
    decToBin(instruction->parametres[0], 26, x);
    decToBin(instruction->OPcodeOrFunc, 6, OPcode);

    sprintf(output, "%s%s", OPcode, x);
}

void setOutputFull(Instruction *instruction, char *output) {
    switch (instruction->format) {
        case FORMAT_1:
            // printf("     1");
            setOutputJ(instruction, output);
            break;
        case FORMAT_2:
        case FORMAT_3:
        case FORMAT_4:
        case FORMAT_5:
        case FORMAT_6:
            // printf("     2");
            setOutputI(instruction, output);
            break;
        default:
            // printf("     3");
            setOutputR(instruction, output);
            break;
    }
}

void getOutput(Instruction *instruction, char *output) {
    char instructionBin[33];
    setOutputFull(instruction, instructionBin);
    binToHex(instructionBin, output);
}
