#include <stdio.h>

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "Instruction.h"

#endif

void readAuto(FILE *, FILE *, int[32]);

void readPas(FILE *, int[32]);

int readLine(FILE *, int, char *, Instruction *, char *);

void analyseLine(char *, Instruction *);

void setOperateurFromLine(char *, Instruction *);

void setOperateurFormat(Instruction *);

void setOperateurOPcodeOrFunc(Instruction *);

void setInstructionFromLine(char *, Instruction *);

void setNbParametersFromLine(Instruction *);

void setParametersFromLine(char *, Instruction *);

void setParametersOrderFromLine(Instruction *);

void checkRegisterExistence(Instruction *, int);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * P A S  E N C O R E  I M P L E M E N T E * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void setValueToRegister(int, int);  // int1 est le numero du registre, int2 est le nombre à stocker

void getValueFromRegister(int, int *);  // int est le numero du registre, int* est l'adresse dans laquelle stocker le nombre

void writeFinalStateRegisters(FILE *, int *);  // int* sont les registres