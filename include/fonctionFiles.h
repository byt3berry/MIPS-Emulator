#include <stdio.h>

#ifndef _FONCTION_FILES_H_
#define _FONCTION_FILES_H_

#include "Instruction.h"

#endif

void readAuto(FILE *, FILE *, int[32]);

void readPas(FILE *, int[32]);

int readLine(FILE *, int, char *, Instruction *, char *);

void analyseLine(char *, Instruction *);

void setOperateurFromLine(char *, Instruction *);

void setOperateurFormat(char *, Instruction *);

void setOperateurOPcodeOrFunc(char *, Instruction *);

void setNbParametersFromLine(char *, Instruction *);

void setParametersFromLine(char *, char *, Instruction *);

void setParametersOrderFromLine(char *, Instruction *);

void checkRegisterExistence(Instruction *, int);

void setInfos(char *, Instruction *);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * P A S  E N C O R E  I M P L E M E N T E * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void setValueToRegister(int, int);  // int1 est le numero du registre, int2 est le nombre à stocker

void getValueFromRegister(int, int *);  // int est le numero du registre, int* est l'adresse dans laquelle stocker le nombre

void writeFinalStateRegisters(FILE *, int *);  // int* sont les registres