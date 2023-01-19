// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#include "memory.h"
#include "constantes.h"

memoryElement memory[MEMORY_SIZE] = {0};


void setValueToMemory(const int address, const int source) {
    int isFound = 0;

    for (int i = 0; i < MEMORY_SIZE && !isFound; i++) {
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
}

void getValueFromMemory(const int address, int *destination) {
    int isFound = 0;
    for (int i = 0; i < MEMORY_SIZE && memory[i].isUsed && !isFound; i++) {
        if (memory[i].address == address) {
            *destination = memory[i].value;
            isFound = 1;
        }
    }

    if (!isFound) {  // si on ne trouve pas en mémoire on renvoie pas défaut 0
        *destination = 0;
    }
}
