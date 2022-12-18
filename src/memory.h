#ifndef MEMORY_H
#define MEMORY_H

#include "constantes.h"


typedef struct memoryElement {
    int address, value, isUsed, isNext;
} memoryElement;


/*
 * memory[2*i]   = adresse dans la mémoire
 * memory[2*i+1] = valeur stockée à cette adresse
 */
extern memoryElement memory[MEMORY_SIZE];

void initMemory();

void setValueToMemory(int, int);

void getValueFromMemory(int, int *);

int findAddressInMemory(int);

void showMemoryStates();

#endif
