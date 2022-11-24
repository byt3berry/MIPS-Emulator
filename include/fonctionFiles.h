#include <stdio.h>

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_
#include "Instruction.h"
#endif


void read(FILE*, int[32]);
void readLine(FILE*, char*, int);
void analyseLine(char*, Instruction*);
void setOperateurFromLine(char*, Instruction*);
void setOperateurFormat(Instruction*);
void setOperateurOPcodeOrFunc(Instruction*);
void setInstructionFromLine(char*, Instruction*);
void setNbParametersFromLine(Instruction*);
void setParametersFromLine(char*, Instruction*);
void setParametersOrderFromLine(Instruction*);
// void setParametersFromLineR(char*, Instruction*);
// void setParametersFromLineI(char*, Instruction*);
// void setParametersFromLineJ(char*, Instruction*);
int getValueFromRegister(int registres[32], char* registre);
int setValueToRegister();
void getFormatStr(char*, Instruction*);