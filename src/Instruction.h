// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "execute.h"
#include "constantes.h"

typedef struct Instruction {
    char line[LINES_LENGTHS_MAX];
    char operateur[8];
    int format;
    int OPcodeOrFunc;
    int nbParameters;
    int parameters[4];
    int parametersOrder[4];
    int outputHex;
    ExecuteFunctions executeFunction;
    int executeParameters[5];
    int error;
} Instruction;

extern Instruction *nextInstruction;


// Setters

void setLine(Instruction *, char *);

void setOperateur(Instruction *, char *);

void setFormat(Instruction *, int);

void setOPcodeOrFunc(Instruction *, int);

void setNbParameters(Instruction *, int);

void setParameters(Instruction *, const int *);

void setParametersOrder(Instruction *, const int *);

void setExecuteFunction(Instruction *, int);

void setExecuteParameters(Instruction *, const int *);

void setOutputR(Instruction *);

void setOutputI(Instruction *);

void setOutputJ(Instruction *);

void setOutput(Instruction *);

void setError(Instruction *, int);


// Getters

char *getLine(Instruction *);

char *getOperateur(Instruction *);

int getFormat(Instruction *);

int getOPcode(Instruction *);

int getNbParameters(Instruction *);

int *getParameters(Instruction *);

int *getParametersOrder(Instruction *);

int getOutput(Instruction *);

int *getExecuteParameters(Instruction *);

int getError(Instruction *);


// Debug

void printInfos(Instruction *);

void showError(Instruction *);


// Autre

int executeInstruction(Instruction *);

int isJumpOrBranch(Instruction *);


#endif