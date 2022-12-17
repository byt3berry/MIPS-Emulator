#include "execute.h"
//#include "Instruction.h"
#include "registers.h"
#include "constantes.h"
#include "utils.h"


//void execute(Instruction *instruction) {
//
//}

// parameters = [target, link, isRegister]
void jump(int *registers, int *parameters) {
    int PCupper = 0;
    int offset = 0;
    int PCvalue;
    getValueFromRegister(registers, PC, &PCvalue);

    if (parameters[2] == 'y') {
        parameters[0] = registers[parameters[0]];
    } else if (parameters[1] == 'y') {
        setValueToRegister(registers, 31, PCvalue);
        offset = 2;
    } else {
        PCupper = getPCupper(PCvalue);
        offset = 2;
    }

    setValueToRegister(registers, PC, PCupper | (parameters[0] << offset));
}

// parameters = [x1, x2, condition, offset]
void branch(int *registers, int *parameters) {
    int result = 0;
    int PCvalue;
    getValueFromRegister(registers, PC, &PCvalue);

    switch (parameters[2]) {
        case '<':
            result = parameters[0] <= parameters[1];
            break;
        case '>':
            result = parameters[0] > parameters[1];
            break;
        case '=':
            result = parameters[0] == parameters[1];
            break;
        case '!':
            result = parameters[0] != parameters[1];
            break;
        default:
            break;
    }

    if (result) {
        incrementPC(registers, parameters[3]);
    }

}

// parameters = [x1, x2, x3, isReverse]
void shiftLeft(int *registers, int *parameters) {
    unsigned int shift;
    int toShift;

    if (parameters[2] == -16) {
        shift = 16;
        toShift = parameters[1];
    } else {
        shift = parameters[2];
        toShift = registers[parameters[1]];
    }

    if (parameters[3] == 'y') {
        setValueToRegister(registers, parameters[0], toShift >> shift);
    } else {
        setValueToRegister(registers, parameters[0], toShift << shift);
    }
}

// parameters = [x1, x2, x3, isSub, isImmediate]
void add(int *registers, int *parameters) {
    int param1, param2;
    getValueFromRegister(registers, parameters[1], &param1);

    if (parameters[4] == 'y') {
        param2 = parameters[2];
    } else {
        getValueFromRegister(registers, parameters[2], &param2);
    }

    param2 = (parameters[3] == 'y') ? -param2 : param2;
    setValueToRegister(registers, parameters[0], param1 + param2);
}

// parameters = [x1, x2, x3, operation]
void logical(int *registers, int *parameters) {
    int result = 0;
    int param1, param2;
    getValueFromRegister(registers, parameters[1], &param1);
    getValueFromRegister(registers, parameters[2], &param2);

    switch (parameters[3]) {
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

    setValueToRegister(registers, parameters[0], result);
}

// parameters = [x, HIorLO]
void moveFrom(int *registers, int *parameters) {
    int result;

    if (parameters[1] == 'H') {
        getValueFromRegister(registers, HI, &result);
    } else {
        getValueFromRegister(registers, LO, &result);
    }

    setValueToRegister(registers, parameters[0], result);
}

// parameters = [x1, x2, x3]
void rotate(int *registers, int *parameters) {
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
    getValueFromRegister(registers, parameters[1], &param1);
    int param2 = parameters[2] % 32; // une rotation de 32 + n bits équivaut à une rotation de n bits
    int upperNbits = param1 & (int) getUpperBits(32 - param2, 32);
    int lowerNbits = param1 & (int) getLowerBits(param2);
    int upperNbitsShifted = upperNbits >> param2;
    int lowerNbitsShifted = lowerNbits << (32 - param1);

    setValueToRegister(registers, parameters[0], lowerNbitsShifted | upperNbitsShifted);
}

// parameters = [x1, x2]
void divide(int *registers, int *parameters) {
    int toDivide, divisor;
    getValueFromRegister(registers, parameters[0], &toDivide);
    getValueFromRegister(registers, parameters[1], &divisor);

    setValueToRegister(registers, HI, toDivide % divisor);
    setValueToRegister(registers, LO, toDivide / divisor);
}

// parameters = [x1, x2]
void multiply(int *registers, int *parameters) {
    int param1, param2;
    long result;
    long lower32bits = getLowerBits(32);
    long upper32bits = getUpperBits(32, 64);
    getValueFromRegister(registers, parameters[0], &param1);
    getValueFromRegister(registers, parameters[1], &param2);

    result = param1 * param2;
    setValueToRegister(registers, LO, (int) (result & lower32bits));
    setValueToRegister(registers, HI, (int) ((result & upper32bits) >> 32));
}

// parameters = [x1, x2, x3, LorS]
void memory(int *registers, int *parameters) {

}
