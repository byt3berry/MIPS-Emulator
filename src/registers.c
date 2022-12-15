#include "registers.h"


void setValueToRegister(int *registers, const int registerNumber, const int x) {
    registers[registerNumber] = x;
}

void getValueFromRegister(const int *registers, const int registerNumber, int *x) {
    *x = registers[registerNumber];
}