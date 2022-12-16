#include "execute.h"
#include "registers.h"
#include "constantes.h"
#include "utils.h"

void execute(Instruction *instruction, int *registers) {
}

void jump(int *registers, int target, const int link, const int isRegister) {
    int PCupper = 0;
    int offset = 0;
    int PCvalue;
    getValueFromRegister(registers, PC, &PCvalue);

    if (isRegister) {
        target = registers[target];
    } else if (link) {
        setValueToRegister(registers, 31, PCvalue);
        offset = 2;
    } else {
        PCupper = getPCupper(PCvalue);
        offset = 2;
    }

    setValueToRegister(registers, PC, PCupper | (target << offset));
}

void branch(int *registers, const int x1, const int x2, const char condition, const int offset) {
    int result = 0;
    int PCvalue;
    getValueFromRegister(registers, PC, &PCvalue);

    switch (condition) {
        case '<':
            result = x1 <= x2;
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

void shiftLeft(int *registers, const int x1, const int x2, const int x3, const char isReverse) {
    unsigned int shift;
    int toShift;

    if (x3 == -16) {
        shift = 16;
        toShift = x2;
    } else {
        shift = x3;
        toShift = registers[x2];
    }

    if (isReverse) {
        setValueToRegister(registers, x1, toShift >> shift);
    } else {
        setValueToRegister(registers, x1, toShift << shift);
    }
}

void add(int *registers, const int x1, const int x2, const int x3, const char isSub, const char isImmediate) {
    int param1, param2;
    getValueFromRegister(registers, x2, &param1);

    if (isImmediate) {
        param2 = x3;
    } else {
        getValueFromRegister(registers, x3, &param2);
    }

    param2 = (isSub) ? -param2 : param2;
    setValueToRegister(registers, x1, param1 + param2);
}

void logical(int *registers, const int x1, const int x2, const int x3, const char operation) {
    int result = 0;
    int param1, param2;
    getValueFromRegister(registers, x2, &param1);
    getValueFromRegister(registers, x3, &param2);

    switch (operation) {
        case '&':
            result = param1 & param2;
            break;
        case '|':
            result = param1 | param2;
            break;
        case '^':
            result = param1 ^ param2;
            break;
        case '<':
            result = param1 < param2;
            break;
        default:
            break;
    }

    setValueToRegister(registers, x1, result);
}

void moveFrom(int *registers, const int x, const char HIorLO) {
    int result;

    if (HIorLO == 'H') {
        getValueFromRegister(registers, HI, &result);
    } else {
        getValueFromRegister(registers, LO, &result);
    }

    setValueToRegister(registers, x, result);
}

void rotate(int *registers, const int x1, const int x2, const int x3) {
    // on va effectuer une rotation vers la gauche pour simplifier le code
    /*
     * Exemple pour rotate 0b10010 de 3 bits vers la droite : (exemple sur 5 bits pour simplifier)
     * upperNbits = 0b10010 & 0b11000 = 0b10000
     * lowerNbits = 0b10010 & 0b00111 = 0b00010
     * upperNbitsShifted = 0b10000 >> 3 = 0b00010
     * lowerNbitsShifted = 0b00010 << 2 = 0b01000
     * output = lowerNbitsShifted | upperNbitsShifted = 0b01010
     */

    int param1;
    getValueFromRegister(registers, x2, &param1);
    int param2 = x3 % 32; // une rotation de 32 + n bits équivaut à une rotation de n bits
    int upperNbits = param1 & (int) getUpperBits(32 - param2, 32);
    int lowerNbits = param1 & (int) getLowerBits(param2);
    int upperNbitsShifted = upperNbits >> param2;
    int lowerNbitsShifted = lowerNbits << (32 - param1);

    setValueToRegister(registers, x1, lowerNbitsShifted | upperNbitsShifted);
}

void divide(int *registers, const int x1, const int x2) {
    int toDivide, divisor;
    getValueFromRegister(registers, x1, &toDivide);
    getValueFromRegister(registers, x2, &divisor);

    setValueToRegister(registers, HI, toDivide % divisor);
    setValueToRegister(registers, LO, toDivide / divisor);
}

void multiply(int *registers, const int x1, const int x2) {
    int param1, param2;
    long result;
    long lower32bits = getLowerBits(32);
    long upper32bits = getUpperBits(32, 64);
    getValueFromRegister(registers, x1, &param1);
    getValueFromRegister(registers, x2, &param2);

    result = param1 * param2;
    setValueToRegister(registers, LO, (int) (result & lower32bits));
    setValueToRegister(registers, HI, (int) ((result & upper32bits) >> 32));
}

//void memory(int *registers, const int x1, const int x2, const int x3, const char LorS) {
//
//}
