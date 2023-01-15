#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "execute.h"
#include "constantes.h"

typedef struct Instruction {
    char line[LINES_LENGTHS_MAX];  // TODO : inutile
    char operateur[8];
    int format;
    int OPcodeOrFunc;
    int nbParameters;
    int parameters[4];
    int parametersOrder[4];
    ExecuteFunctions executeFunction;
    int executeParameters[5];
    int error;
} Instruction;

extern Instruction *nextInstruction;

void setLine(Instruction *, char *);

void setOperateur(Instruction *, char *);

void setFormat(Instruction *, int);

void setOPcodeOrFunc(Instruction *, int);

void setNbParameters(Instruction *, int);

void setParameters(Instruction *, const int *);

void setParametersOrder(Instruction *, const int *);

void setExecuteFunction(Instruction *, int);

void setExecuteParameters(Instruction *, const int *);

void setOutputR(Instruction *, int *);

void setOutputI(Instruction *, int *);

void setOutputJ(Instruction *, int *);

void getOutput(Instruction *, int *);

void executeInstruction(Instruction *);

void printInfos(Instruction *);

void setError(Instruction *, int);

int isError(Instruction *);

void showError(Instruction *);

#endif