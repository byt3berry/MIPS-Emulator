#include <stdio.h>
#ifndef REGISTERS_H_
#define REGISTERS_H_
#endif


void setValueToRegister(int *, int, int);  // int1 est le numero du registre, int2 est le nombre à stocker

void getValueFromRegister(const int *, int, int *);  // int est le numero du registre, int* est l'adresse dans laquelle stocker le nombre

void writeFinalStateRegisters(int *, FILE *);  // int* sont les registres, si FILE* == NONE => ecrire les registres dans la console