#include "memory.h"
#include "constantes.h"
#include <stdio.h>

memoryElement memory[MEMORY_SIZE] = {0};


void setValueToMemory(const int address, const int source) {
    int isFound = 0;
    int i = 0;
    for (; i < MEMORY_SIZE && !isFound; i++) {
        if (memory[i].isUsed && memory[i].address == address) {
            memory[i].value = source;
            isFound = 1;
        } else if (!memory[i].isUsed) {
            memory[i].address = address;
            memory[i].value = source;
            memory[i].isUsed = 1;
            isFound = 1;
        }
    }

    // TODO: Warning si la mémoire est pleine
}

void getValueFromMemory(const int address, int *destination) {
    int isFound = 0;
    for (int i = 0; i < MEMORY_SIZE && memory[i].isUsed && !isFound; i++) {
        if (memory[i].address == address) {
            *destination = memory[i].value;
            isFound = 1;
        }
    }

    // TODO: Warning si on accède à une zone mémoire non allouée
}

void showMemoryStates() {
    for (int i = 0; i < MEMORY_SIZE /*&& memory[i].isNext*/; i++) {
        printf("MEM[%d] : %d : %d\n", memory[i].address, memory[i].value, memory[i].isUsed);
    }
}