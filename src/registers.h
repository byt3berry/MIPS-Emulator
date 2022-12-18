#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <stdio.h>

extern int registers[35];

void setValueToRegister(int *, int, int);  // int1 est le numero du registre, int2 est le nombre à stocker

void getValueFromRegister(const int *, int, int *);  // int est le numero du registre, int* est l'adresse dans laquelle stocker le nombre

int getPCupper(int);  // unsigned int est la valeur de PC

void incrementPC(int *, int);  // int* est l'adresse des registres, int est la valeur d'incrémentation

void showRegistersStates(int *);

void writeFinalStateRegisters(int *, FILE *);  // int* sont les registres, si FILE* == NONE => ecrire les registres dans la console

#endif
