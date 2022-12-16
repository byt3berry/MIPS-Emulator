#include "registers.h"
#include "constantes.h"


void setValueToRegister(int *registers, const int registerNumber, const int source) {
    registers[registerNumber] = source;
}

void getValueFromRegister(const int *registers, const int registerNumber, int *destination) {
    *destination = registers[registerNumber];
}

void jump(int *registers, const int target, const int link) {
    int PCupper = 0;
    int PCvalue;
    getValueFromRegister(registers, PC, &PCvalue);

    if (link) {
        setValueToRegister(registers, 31, PCvalue);
    } else {
        PCupper = getPCupper(PCvalue);
    }

    setValueToRegister(registers, PC, PCupper | (target << 2));
}

void branch(int *registers, const int x1, const int x2, const char condition, const int offset) {
    int result = 0;
    int PCvalue;
    getValueFromRegister(registers, PC, &PCvalue);

    switch (condition) {
        case '<':
            result = x1 < x2;
            break;
        case '>':
            result = x1 > x2;
            break;
        case '=':
            result = x1 == x2;
            break;
        case '!':
            result = x1 != x2;
            break;
        default:
            break;
    }

    if (result) {
        incrementPC(registers, offset);
    }

}

int getPCupper(const int PCvalue) {
    unsigned int PCupper = 0b11110000000000000000000000000000;  // pour recuperer les 4 bits de poids fort de PC
    return PCvalue & ((int) PCupper);
}

void incrementPC(int *registers, const int offset) {
    int pcValue;
    getValueFromRegister(registers, PC, &pcValue);
    setValueToRegister(registers, PC, pcValue + offset * 4);
}
