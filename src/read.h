// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#ifndef READ_H
#define READ_H

#include <stdio.h>
#include "Instruction.h"
#include "constantes.h"

void readInteractif();

void readAuto(FILE *, FILE *, FILE *);

void readPas(FILE *);

int getAllInstructionsInFile(FILE *, Instruction *[LINES_NUMBER_MAX]);

void assemble(FILE *, Instruction *[LINES_NUMBER_MAX]);

int execute(Instruction *[LINES_NUMBER_MAX], int, int);

void freeAll(Instruction *[LINES_NUMBER_MAX]);

#endif
