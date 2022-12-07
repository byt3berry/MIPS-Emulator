#include <stdio.h>

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "Instruction.h"

#endif


void analyseLine(char *, Instruction *);

void setOperateurFromLine(char *, Instruction *);

void setOperateurFormat(char *, Instruction *);

void setOperateurOPcodeOrFunc(char *, Instruction *);

void setNbParametersFromLine(char *, Instruction *);

void setParametersFromLine(char *, char *, Instruction *);

void setParametersOrderFromLine(char *, Instruction *);

void checkRegisterExistence(Instruction *, int);

void setInfos(char *, Instruction *);