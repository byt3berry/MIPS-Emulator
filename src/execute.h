#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_
#include "Instruction.h"
#endif

void execute(Instruction *);

void executeI(Instruction *);

void executeJ(Instruction *);

void executeR(Instruction *);

int add(int, int);

int substract(int, int);

int multiply(int, int);

int divide(int, int);

int and(int, int);

int or(int, int);

int xor(int, int);

int modulo(int, int);

int shiftLeft(int, int);

int shiftRight(int, int);

int rotate(int, int);

int condition(int, int, char);