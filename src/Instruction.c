#include <stdio.h>
#include <string.h>

#include "Instruction.h"
#include "utils.h"
#include "constantes.h"


void printInfos(Instruction *instruction) {
    printf("operateur     : %s\n", instruction->operateur);
    printf("format        : %d\n", instruction->format);
    printf("OPcodeOrFunc  : %d\n", instruction->OPcodeOrFunc);
    printf("nbParameters  : %d\n", instruction->nbParameters);
    printf("Ordre         : %d %d %d %d\n", instruction->parametersOrder[0], instruction->parametersOrder[1], instruction->parametersOrder[2], instruction->parametersOrder[3]);
    printf("x1            : %d\n", instruction->parameters[0]);
    printf("x2            : %d\n", instruction->parameters[1]);
    printf("x3            : %d\n", instruction->parameters[2]);
    printf("x4            : %d\n", instruction->parameters[3]);
    printf("error         : %d\n", instruction->error);
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

void setNbParameters(Instruction *instruction, int nbParameters) {
    instruction->nbParameters = nbParameters;
}

void setParameters(Instruction *instruction, int *parameters) {
    for (int i = 0; i < 4; i++) {
        if (i < instruction->nbParameters) {
            instruction->parameters[i] = parameters[i];
        } else {
            instruction->parameters[i] = 0;
        }
    }
}

void setParametersOrder(Instruction *instruction, int *parametersOrder) {
    for (int i = 0; i < 4; i++) {
        instruction->parametersOrder[i] = parametersOrder[i];
    }
}

void setOutputR(Instruction *instruction, char *output) {
    int parameters[4];

    for (int i = 0; i < 4; i++) {
        int index = instruction->parametersOrder[i];
        if (index == 0) {
            parameters[i] = 0;
        } else if (index == -1) {
            parameters[i] = 1;
        } else {
            parameters[i] = instruction->parameters[index - 1];
        }
    }

    char OPcode[OPCODE_FUNC_SIZE + 1], func[OPCODE_FUNC_SIZE + 1];
    char x1[REGISTER_SIZE + 1], x2[REGISTER_SIZE + 1], x3[REGISTER_SIZE + 1], x4[REGISTER_SIZE + 1];

    decToBin(0, OPCODE_FUNC_SIZE, OPcode);
    decToBin(instruction->OPcodeOrFunc, OPCODE_FUNC_SIZE, func);
    decToBin(parameters[0], REGISTER_SIZE, x1);
    decToBin(parameters[1], REGISTER_SIZE, x2);
    decToBin(parameters[2], REGISTER_SIZE, x3);
    decToBin(parameters[3], REGISTER_SIZE, x4);

//    printf("%s\n", OPcode);
//    printf("%s\n", x1);
//    printf("%s\n", x2);
//    printf("%s\n", x3);
//    printf("%s\n", x4);
//    printf("%s\n", func);

    sprintf(output, "%s%s%s%s%s%s", OPcode, x1, x2, x3, x4, func);
}

void setOutputI(Instruction *instruction, char *output) {
    int parameters[3];

    for (int i = 0; i < 3 && instruction->parametersOrder[i] != -2; i++) {
        int index = instruction->parametersOrder[i];
        if (index == 0) {
            parameters[i] = 0;
        } else if (index == -1) {
            parameters[i] = 1;
        } else {
            parameters[i] = instruction->parameters[index - 1];
        }
    }

    char OPcode[OPCODE_FUNC_SIZE + 1];
    char x1[REGISTER_SIZE + 1], x2[REGISTER_SIZE + 1], x3[I_IMMEDIATE_SIZE + 1];

    decToBin(instruction->OPcodeOrFunc, OPCODE_FUNC_SIZE, OPcode);
    decToBin(parameters[0], REGISTER_SIZE, x1);
    decToBin(parameters[1], REGISTER_SIZE, x2);
    decToBin(parameters[2], I_IMMEDIATE_SIZE, x3);

    sprintf(output, "%s%s%s%s", OPcode, x1, x2, x3);
}

void setOutputJ(Instruction *instruction, char *output) {
    char OPcode[OPCODE_FUNC_SIZE + 1];
    char x[J_TARGET_SIZE + 1];

    decToBin(instruction->OPcodeOrFunc, OPCODE_FUNC_SIZE, OPcode);
    decToBin(instruction->parameters[0], J_TARGET_SIZE, x);

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
    char instructionBin[BINARY_CODE_SIZE + 1];
    setOutputFull(instruction, instructionBin);
    binToHex(instructionBin, output);
}

void setNOP(Instruction *instruction) {
    int zeroArray[4] = {0};

    setOperateur(instruction, "NOP\0");
    setFormat(instruction, 13);
    setNbParameters(instruction, 0);
    setParameters(instruction, zeroArray);
    setOPcodeOrFunc(instruction, 0);
    setParametersOrder(instruction, zeroArray);
}

void setError(Instruction *instruction, int error) {
    instruction->error = error;
//    showError(instruction);
}

int isError(Instruction *instruction) {
    return instruction->error;
}

void showError(Instruction *instruction) {
    switch (instruction->error) {
        case NO_ERROR:
            printf("Aucune erreur détéctée !!\n");
            break;
        case BAD_OPERATEUR:
            printf("L'opérateur entré n'existe pas\n");
            break;
        case BAD_NBPARAMETERS:
            printf("Le nombre de paramètres entré ne correspond pas avec l'opérateur\n");
            break;
        case BAD_REGISTER:
            printf("Le(s) registre(s) entré(s) ne correspond(ent) n'existe(nt) pas\n");
            break;
    }
}