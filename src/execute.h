#ifndef EXECUTE_H
#define EXECUTE_H

//#include "Instruction.h"

//void execute(Instruction *);

void jump(int *, const int *, const int *);

void branch(int *, const int *, const int *);

void shiftLeft(int *, const int *, const int *);

void add(int *, const int *, const int *);

void logical(int *, const int *, const int *);

void moveFrom(int *, const int *, const int *);

void rotate(int *, const int *, const int *);

void divide(int *, const int *, const int *);

void multiply(int *, const int *, const int *);

void memory(int *, const int *, const int *);

#endif


