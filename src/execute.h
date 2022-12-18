#ifndef EXECUTE_H
#define EXECUTE_H

//#include "Instruction.h"

//void execute(Instruction *);

void jump(const int *, const int *);

void branch(const int *, const int *);

void shiftLeft(const int *, const int *);

void add(const int *, const int *);

void logical(const int *, const int *);

void moveFrom(const int *, const int *);

void rotate(const int *, const int *);

void divide(const int *, const int *);

void multiply(const int *, const int *);

void memoryAccess(const int *, const int *);

void nothing(const int *, const int *);

#endif


