#ifndef READ_H
#define READ_H

#include <stdio.h>
#include "Instruction.h"

void readInteractif();

void readAuto(FILE *, FILE *);

void readPas(FILE *);

int readLine(FILE *, int, char *, Instruction *, char *);

#endif
