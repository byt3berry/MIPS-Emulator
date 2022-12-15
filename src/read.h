#include <stdio.h>

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_
#include "Instruction.h"
#endif

void readInteractif(int[32]);

void readAuto(FILE *, FILE *, int[32]);

void readPas(FILE *, int[32]);

int readLine(FILE *, int, char *, Instruction *, char *);