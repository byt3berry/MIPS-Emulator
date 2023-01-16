#include <stdio.h>
#include <string.h>

#include "Instruction.h"
#include "utils.h"
#include "constantes.h"


Instruction *nextInstruction = NULL;

void printInfos(Instruction *instruction) {
    printf("operateur     : %s\n", instruction->operateur);
    printf("format        : %d\n", instruction->format);
    printf("OPcodeOrFunc  : %d\n", instruction->OPcodeOrFunc);
    printf("nbParameters  : %d\n", instruction->nbParameters);
    printf("Ordre         : %d %d %d %d\n", instruction->parametersOrder[0], instruction->parametersOrder[1], instruction->parametersOrder[2], instruction->parametersOrder[3]);
    printf("parameters1   : %d\n", instruction->parameters[0]);
    printf("parameters2   : %d\n", instruction->parameters[1]);
    printf("parameters3   : %d\n", instruction->parameters[2]);
    printf("parameters4   : %d\n", instruction->parameters[3]);
    printf("exePara1      : %d\n", instruction->executeParameters[0]);
    printf("exePara2      : %d\n", instruction->executeParameters[1]);
    printf("exePara3      : %d\n", instruction->executeParameters[2]);
    printf("exePara4      : %d\n", instruction->executeParameters[3]);
    printf("exePara5      : %d\n", instruction->executeParameters[4]);
//    printf("error         : %d\n", instruction->error);
}

void setLine(Instruction *instruction, char *line) {
    strcpy(instruction->line, line);
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

void setParameters(Instruction *instruction, const int *parameters) {
    for (int i = 0; i < 4; i++) {
//        printf("Parametre : %d\n", parameters[i]);
        if (i < instruction->nbParameters) {
            instruction->parameters[i] = parameters[i];
        } else {
            instruction->parameters[i] = 0;
        }
    }
}

void setParametersOrder(Instruction *instruction, const int *parametersOrder) {
    for (int i = 0; i < 4; i++) {
        instruction->parametersOrder[i] = parametersOrder[i];
    }
}

void setExecuteFunction(Instruction *instruction, const int executeFunction) {
    if (0 <= executeFunction && executeFunction <= 9) {
        instruction->executeFunction = executeFunctions[executeFunction];
    } else {
        instruction->executeFunction = NULL;
    }
}

void setExecuteParameters(Instruction *instruction, const int *executeParameters) {
    for (int i = 0; i < 5; i++) {
        int index = executeParameters[i];
        if (index == '~') {
            instruction->executeParameters[i] = 0;
        } else {
            instruction->executeParameters[i] = index;
        }
    }
}

void setOutputR(Instruction *instruction) {
    int parameters[4];
    long OPcode, x1, x2, x3, x4, func;

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

    OPcode = 0 << 26;
    x1 = parameters[0] << 21 & getUpperBits(5, 26);
    x2 = parameters[1] << 16 & getUpperBits(5, 21);
    x3 = parameters[2] << 11 & getUpperBits(5, 16);
    x4 = parameters[3] << 6 & getUpperBits(5, 11);
    func = instruction->OPcodeOrFunc & getLowerBits(6);

    instruction->outputHex = (int) (OPcode + x1 + x2 + x3 + x4 + func);
}

void setOutputI(Instruction *instruction) {
    int parameters[3];
    long OPcode, x1, x2, x3;

    for (int i = 0; i < 3 && instruction->parametersOrder[i] != '~'; i++) {
        int index = instruction->parametersOrder[i];
        if (index == 0) {
            parameters[i] = 0;
        } else if (index == -1) {
            parameters[i] = 1;
        } else {
            parameters[i] = instruction->parameters[index - 1];
        }
    }

    OPcode = instruction->OPcodeOrFunc << 26 & getUpperBits(6, 32);
    x1 = parameters[0] << 21 & getUpperBits(5, 26);
    x2 = parameters[1] << 16 & getUpperBits(5, 21);
    x3 = parameters[2] & getLowerBits(16);
    instruction->outputHex = (int) (OPcode + x1 + x2 + x3);
}

void setOutputJ(Instruction *instruction) {
    long OPcode, x;

    OPcode = instruction->OPcodeOrFunc << 26 & getUpperBits(6, 32);
    x = instruction->parameters[0] & getLowerBits(26);

    instruction->outputHex = (int) (OPcode + x);
}

void setOutput(Instruction *instruction) {
    int format = instruction->format;

    if (format == FORMAT_1) {
        setOutputJ(instruction);
    } else if (FORMAT_2 <= format && format <= FORMAT_6) {
        setOutputI(instruction);
    } else {
        setOutputR(instruction);
    }
}

int getOutput(Instruction *instruction) {
    return instruction->outputHex;
}

int executeInstruction(Instruction *instruction) {
    int isError = 0;
    if (instruction->executeFunction != NULL) {
        isError = instruction->executeFunction(instruction->executeParameters, instruction->parameters);
    }

    return isError;
}

int isJumpOrBranch(Instruction *instruction) {
    int format = instruction->format;

    if (format == 1 || format == 3 || format == 5 || format == 12) {
        return 1;
    }

    return 0;
}

void setError(Instruction *instruction, int error) {
    instruction->error = error;
    showError(instruction);
}

int isError(Instruction *instruction) {
    return instruction->error;
}

void showError(Instruction *instruction) {
    switch (instruction->error) {
        case NO_ERROR:
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
        case OVERFLOW_PARAM:
            printf("La valeur immédiate entrée est trop grande (>32bits)");
            break;
        case OVERFLOW_RESULT:
            printf("Le résultat immédiate entrée est trop grande (>32bits)");
            break;
        case BAD_ADDRESS:
            printf("L'adresse entrée doit être un multiple de 4");
            break;
        default:
            printf("Autre erreur ????\n");
            break;
    }
}