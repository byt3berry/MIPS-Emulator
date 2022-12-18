#include "memory.h"
#include "constantes.h"
#include <stdio.h>

memoryElement memory[MEMORY_SIZE] = {0};

void initMemory() {
    memoryElement element;
    element.address = 0;
    element.value = 0;
    element.isUsed = 0;
    element.isNext = 0;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = element;
    }

    memory[0].isNext = 1;
}

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

//int findAddressInMemory(const int address) {
//    int index = -1;
//    for (int i = 0; i < 100 && index == -1; i += 2) {
//        if (memory[i] == address) {
//            index = i;
//        }
//    }
//
//    return index;
//}

void showMemoryStates() {
    for (int i = 0; i < MEMORY_SIZE /*&& memory[i].isNext*/; i++) {
        printf("MEM[%d] : %d : %d : %d\n", memory[i].address, memory[i].value, memory[i].isUsed, memory[i].isNext);
    }
}