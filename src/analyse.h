#include <stdio.h>

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "Instruction.h"

#endif


void analyseLine(char *, Instruction *);

void analyseHex(int, Instruction *);

void setOperateurFromLine(char *, Instruction *);

void formatLine(char *);

void setOperateurFormat(char *, Instruction *);

void setOperateurOPcodeOrFunc(char *, Instruction *);

void setNbParametersFromLine(char *, Instruction *);

void setParametersFromLine(char *, char *, Instruction *);

void setParametersFromHex(int, Instruction *);

void setParametersOrderFromLine(char *, Instruction *);

void setExecuteFunctionFromLine(char *, Instruction *);

void setExecuteParametersFromLine(char *, Instruction *);

void formatParameter(char *, int *);

void checkRegisterExistence(Instruction *, char *, int *);

int findRegisterNumber(char *);
