#ifndef READ_H
#define READ_H

#include <stdio.h>
#include "Instruction.h"
#include "constantes.h"

void readInteractif();

void readAuto(FILE *, FILE *, FILE *);

void readPas(FILE *);

int getAllInstructionsInFile(FILE *, Instruction *[LINES_NUMBER_MAX], int);

void assemble(FILE *, Instruction *[LINES_NUMBER_MAX], int);

int execute(Instruction *[LINES_NUMBER_MAX], int);

void freeAll(Instruction *[LINES_NUMBER_MAX]);

#endif
