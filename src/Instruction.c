#include <stdio.h>
#include <string.h>

#include "../include/Instruction.h"
#include "../include/utils.h"
#include "constantes.c"

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

    char OPcode[OPCODE_FUNC_SIZE+1], func[OPCODE_FUNC_SIZE+1];
    char x1[REGISTER_SIZE+1], x2[REGISTER_SIZE+1], x3[REGISTER_SIZE+1], x4[REGISTER_SIZE+1];

    decToBin(0, OPCODE_FUNC_SIZE, OPcode);
    decToBin(instruction->OPcodeOrFunc, OPCODE_FUNC_SIZE, func);
    decToBin(parametres[0], REGISTER_SIZE, x1);
    decToBin(parametres[1], REGISTER_SIZE, x2);
    decToBin(parametres[2], REGISTER_SIZE, x3);
    decToBin(parametres[3], REGISTER_SIZE, x4);

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

    char OPcode[OPCODE_FUNC_SIZE+1];
    char x1[REGISTER_SIZE+1], x2[REGISTER_SIZE+1], x3[I_IMMEDIATE_SIZE+1];

    decToBin(instruction->OPcodeOrFunc, OPCODE_FUNC_SIZE, OPcode);
    decToBin(parametres[0], REGISTER_SIZE, x1);
    decToBin(parametres[1], REGISTER_SIZE, x2);
    decToBin(parametres[2], I_IMMEDIATE_SIZE, x3);

    sprintf(output, "%s%s%s%s", OPcode, x1, x2, x3);
}

void setOutputJ(Instruction *instruction, char *output) {
    char OPcode[OPCODE_FUNC_SIZE];
    char x[J_TARGET_SIZE+1];

    decToBin(instruction->OPcodeOrFunc, OPCODE_FUNC_SIZE, OPcode);
    decToBin(instruction->parametres[0], J_TARGET_SIZE, x);

    sprintf(output, "%s%s", OPcode, x);
}

void setOutputFull(Instruction *instruction, char *output) {
    int format = instruction->format;

    if (format == FORMAT_1) {
        setOutputJ(instruction, output);
    } else if (FORMAT_2 <= format && format <= FORMAT_6) {
        setOutputI(instruction, output);
    } else {
        setOutputR(instruction, output);
    }
}

void getOutput(Instruction *instruction, char *output) {
    char instructionBin[BINARY_CODE_SIZE+1];
    setOutputFull(instruction, instructionBin);
    binToHex(instructionBin, output);
}
