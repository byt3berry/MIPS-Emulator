#include <stdio.h>

#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#endif


void setValueToRegister(int, int);  // int1 est le numero du registre, int2 est le nombre à stocker

void getValueFromRegister(int, int *);  // int est le numero du registre, int* est l'adresse dans laquelle stocker le nombre

void writeFinalStateRegisters(FILE *, int *);  // int* sont les registres