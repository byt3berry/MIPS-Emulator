#include <stdio.h>

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "Instruction.h"

#endif

void readAuto(FILE *, FILE *, FILE *, int[32]);

void readPas(FILE *, int[32]);

void readLine(FILE *, char *, int);

void write(FILE *, char *);

void analyseLine(char *, Instruction *);

void setOperateurFromLine(char *, Instruction *);

void setOperateurFormat(Instruction *);

void setOperateurOPcodeOrFunc(Instruction *);

void setInstructionFromLine(char *, Instruction *);

void setNbParametersFromLine(Instruction *);

void setParametersFromLine(char *, Instruction *);

void setParametersOrderFromLine(Instruction *);

int getValueFromRegister(int registres[32], char *registre);

int setValueToRegister();

void getFormatStr(char *, Instruction *);