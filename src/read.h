#ifndef READ_H
#define READ_H

#include <stdio.h>
#include "Instruction.h"

void readInteractif(int[32]);

void readAuto(FILE *, FILE *, int[32]);

void readPas(FILE *, int[32]);

int readLine(FILE *, int, char *, Instruction *, char *);

#endif
