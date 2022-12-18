#ifndef MEMORY_H
#define MEMORY_H

#include "constantes.h"


typedef struct memoryElement {
    int address, value, isUsed;
} memoryElement;


extern memoryElement memory[MEMORY_SIZE];

void setValueToMemory(int, int);

void getValueFromMemory(int, int *);

void showMemoryStates();

#endif
