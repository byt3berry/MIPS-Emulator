#ifndef READ_H
#define READ_H

#include <stdio.h>
#include "Instruction.h"

void readInteractif(int *);

void readAuto(FILE *, FILE *, int *);

void readPas(FILE *, int *);

int readLine(FILE *, int *, int, char *, Instruction *, char *);

#endif
