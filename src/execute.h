#ifndef EXECUTE_H
#define EXECUTE_H

#include "Instruction.h"

void execute(Instruction *, int *);

void jump(int *, int, int, int);  // int* est l'adresse des registres, int est la target, int vaut 1 s'il faut link, int vaut 1 si la target est dans un registre

void branch(int *, int, int, char, int);

void shiftLeft(int *, int, int, int, char);

void add(int *, int, int, int, char, char);

void logical(int *, int, int, int, char);

void moveFrom(int *, int, char);

void rotate(int *, int, int, int);

void divide(int *, int, int);

void multiply(int *, int, int);

void memory(int *, int, int, int, char);

#endif
