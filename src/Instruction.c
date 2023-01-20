// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#include <stdio.h>
#include <string.h>

#include "Instruction.h"
#include "utils.h"
#include "constantes.h"


Instruction *nextInstruction = NULL;


// Setters

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
    int *instrParameters = getParameters(instruction);
    int *instrParametersOrder = getParametersOrder(instruction);
    long OPcode, x1, x2, x3, x4, func;

    for (int i = 0; i < 4; i++) {
        int index = instrParametersOrder[i];
        if (index == 0) {
            parameters[i] = 0;
        } else if (index == -1) {
            parameters[i] = 1;
        } else {
            parameters[i] = instrParameters[index - 1];
        }
    }

    int OPcodeShift = OPCODE_FUNC_SIZE + 4 * REGISTER_SIZE;
    int x1Shift = OPCODE_FUNC_SIZE + 3 * REGISTER_SIZE;
    int x2Shift = OPCODE_FUNC_SIZE + 2 * REGISTER_SIZE;
    int x3Shift = OPCODE_FUNC_SIZE + REGISTER_SIZE;
    int x4Shift = OPCODE_FUNC_SIZE;

    OPcode = 0 << OPcodeShift;
    x1 = parameters[0] << x1Shift & getUpperBits(5, 26);
    x2 = parameters[1] << x2Shift & getUpperBits(5, 21);
    x3 = parameters[2] << x3Shift & getUpperBits(5, 16);
    x4 = parameters[3] << x4Shift & getUpperBits(5, 11);
    func = getOPcode(instruction) & getLowerBits(6);

    instruction->outputHex = (int) (OPcode + x1 + x2 + x3 + x4 + func);
}

void setOutputI(Instruction *instruction) {
    int parameters[3];
    int *instrParameters = getParameters(instruction);
    int *instrParametersOrder = getParametersOrder(instruction);
    long OPcode, x1, x2, x3;

    for (int i = 0; i < 3 && instrParametersOrder[i] != '~'; i++) {
        int index = instrParametersOrder[i];
        if (index == 0) {
            parameters[i] = 0;
        } else if (index == -1) {
            parameters[i] = 1;
        } else {
            parameters[i] = instrParameters[index - 1];
        }
    }

    int OPcodeShift = 2 * REGISTER_SIZE + I_IMMEDIATE_SIZE;
    int x1Shift = REGISTER_SIZE + I_IMMEDIATE_SIZE;
    int x2Shift = I_IMMEDIATE_SIZE;

    OPcode = getOPcode(instruction) << OPcodeShift & getUpperBits(6, 32);
    x1 = parameters[0] << x1Shift & getUpperBits(5, 26);
    x2 = parameters[1] << x2Shift & getUpperBits(5, 21);
    x3 = parameters[2] & getLowerBits(16);

    instruction->outputHex = (int) (OPcode + x1 + x2 + x3);
}

void setOutputJ(Instruction *instruction) {
    long OPcode, x;
    int *instrParameters = getParameters(instruction);

    int OPcodeShift = J_TARGET_SIZE;

    OPcode = getOPcode(instruction) << OPcodeShift & getUpperBits(6, 32);
    x = instrParameters[0] & getLowerBits(26);

    instruction->outputHex = (int) (OPcode + x);
}

void setOutput(Instruction *instruction) {
    int format = getFormat(instruction);

    if (format == FORMAT_1) {
        setOutputJ(instruction);
    } else if (FORMAT_2 <= format && format <= FORMAT_6) {
        setOutputI(instruction);
    } else {
        setOutputR(instruction);
    }
}

void setError(Instruction *instruction, int error) {
    instruction->error = error;
    showError(instruction);
}


// Getters

char *getLine(Instruction *instruction) {
    return instruction->line;
}

char *getOperateur(Instruction *instruction) {
    return instruction->operateur;
}

int getFormat(Instruction *instruction) {
    return instruction->format;
}

int getOPcode(Instruction *instruction) {
    return instruction->OPcodeOrFunc;
}

int getNbParameters(Instruction *instruction) {
    return instruction->nbParameters;
}

int *getParameters(Instruction *instruction) {
    return instruction->parameters;
}

int *getParametersOrder(Instruction *instruction) {
    return instruction->parametersOrder;
}

int getOutput(Instruction *instruction) {
    return instruction->outputHex;
}

int *getExecuteParameters(Instruction *instruction) {
    return instruction->executeParameters;
}

int getError(Instruction *instruction) {
    return instruction->error;
}


// Debug

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
    printf("error         : %d\n", instruction->error);
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
        case BAD_ADDRESS:
            printf("L'adresse entrée doit être un multiple de 4");
            break;
        case DIVISION_BY_ZERO:
            printf("Vous essayez de diviser par 0\n");
            break;
        case PAS_A_PAS:
            printf("Cet opérateur n'est pas autorisé en mode Pas à Pas\n");
            break;
        default:
            printf("Autre erreur ????\n");
            break;
    }
}


// Autre

int executeInstruction(Instruction *instruction) {
    int isError = 0;
    ExecuteFunctions executeFunction = instruction->executeFunction;
    if (instruction->executeFunction != NULL) {
        isError = executeFunction(getExecuteParameters(instruction), getParameters(instruction));
    }

    setError(instruction, isError);

    return isError;
}

int isJumpOrBranch(Instruction *instruction) {
    int format = getFormat(instruction);

    if (format == 1 || format == 3 || format == 5 || format == 12) {
        return 1;
    }

    return 0;
}

