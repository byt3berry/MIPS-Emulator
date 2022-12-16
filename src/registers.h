#include <stdio.h>
#ifndef REGISTERS_H_
#define REGISTERS_H_
#endif


void setValueToRegister(int *, int, int);  // int1 est le numero du registre, int2 est le nombre à stocker

void getValueFromRegister(const int *, int, int *);  // int est le numero du registre, int* est l'adresse dans laquelle stocker le nombre

void writeFinalStateRegisters(int *, FILE *);  // int* sont les registres, si FILE* == NONE => ecrire les registres dans la console

void jump(int *, int, int);  // int* est l'adresse des registres, int est la target, int vaut 1 s'il faut link

void branch(int *, int, int, char, int);

int getPCupper(int);  // unsigned int est la valeur de PC

void incrementPC(int *, int);  // int* est l'adresse des registres, int est la valeur d'incrémentation
