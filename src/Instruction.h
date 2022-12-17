#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "execute.h"


typedef struct Instruction {
    char operateur[8];
    int format;
    int OPcodeOrFunc;
    int nbParameters;
    int parameters[4];
    int parametersOrder[4];
    void (*executeFunction)(int *, int *);
    int executeParameters[5];
    int error;
} Instruction;

void setOperateur(Instruction *, char *);

void setFormat(Instruction *, int);

void setOPcodeOrFunc(Instruction *, int);

void setNbParameters(Instruction *, int);

void setParameters(Instruction *, const int *);

void setParametersOrder(Instruction *, const int *);

void setExecuteFunction(Instruction *, int);

void setExecuteParameters(Instruction *, int *);

void setOutputFull(Instruction *, char *);

void setOutputR(Instruction *, char *);

void setOutputI(Instruction *, char *);

void setOutputJ(Instruction *, char *);

void getOutput(Instruction *, char *);

void executeInstruction(Instruction *, int *);

void printInfos(Instruction *);

void setNOP(Instruction *);

void setError(Instruction *, int);

int isError(Instruction *);

void showError(Instruction *);

#endif