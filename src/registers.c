#include "registers.h"
#include "constantes.h"
#include "utils.h"

void setValueToRegister(int *registers, const int registerNumber, const int source) {
    registers[registerNumber] = source;
}

void getValueFromRegister(const int *registers, const int registerNumber, int *destination) {
    *destination = registers[registerNumber];
}

int getPCupper(const int PCvalue) {
    unsigned int PCupper = getUpperBits(4, 32);  // pour recuperer les 4 bits de poids fort de PC
    return PCvalue & ((int) PCupper);
}

void incrementPC(int *registers, const int offset) {
    int pcValue;
    getValueFromRegister(registers, PC, &pcValue);
    setValueToRegister(registers, PC, pcValue + offset * 4);
}

void showRegistersStates(int *registers) {
    for (int i = 0; i < 35; i++) {
        if (registers[i] != -1) {
            printf("register %d : %d\n", i, registers[i]);
        }
    }
}

void writeFinalStateRegisters(int *registers, FILE *fichierFinal) {
    for (int i = 0; i < 32; i++) {
        fprintf(fichierFinal, "$%.2d:%d\n", i, registers[i]);
    }

    fprintf(fichierFinal, "HI:%d\n", registers[HI]);
    fprintf(fichierFinal, "LO:%d\n", registers[LO]);
}