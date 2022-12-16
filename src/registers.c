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
