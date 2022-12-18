#include "execute.h"
//#include "Instruction.h"
#include "registers.h"
#include "constantes.h"
#include "utils.h"
#include <stdlib.h>


//void execute(Instruction *instruction) {
//
//}

// parameters = [target, link, isRegister]
void jump(int *registers, const int *executeParameters, const int *parameters) {
    printf("jump\n");

    int target, link, isRegister;

    target = executeParameters[0];
    link = executeParameters[1];
    isRegister = executeParameters[2];

    int PCupper = 0;
    int offset = 0;
    int PCvalue;
    getValueFromRegister(registers, PC, &PCvalue);

    if (isRegister) {
        getValueFromRegister(registers, parameters[target - 1], &target);
    } else if (link) {
        setValueToRegister(registers, 31, PCvalue);
        offset = 2;
    } else {
        PCupper = getPCupper(PCvalue);
        offset = 2;
    }

    printf("PC = %d | %d << %d", PCupper, target, offset);

    setValueToRegister(registers, PC, PCupper | (target << offset));
}

// parameters = [x1, x2, condition, offset]
void branch(int *registers, const int *executeParameters, const int *parameters) {
    printf("branch\n");

    int x1, x2, condition, offset;

    getValueFromRegister(registers, parameters[executeParameters[0] - 1], &x1);
    getValueFromRegister(registers, parameters[executeParameters[1] - 1], &x2);
    condition = executeParameters[2];
    offset = executeParameters[3];

    int result = 0;
    int PCvalue;
    getValueFromRegister(registers, PC, &PCvalue);

    switch (condition) {
        case 0:
            printf("if (%d == %d) : PC += %d", x1, x2, offset);
            result = x1 == x2;
            break;
        case 1:
            printf("if (%d != %d) : PC += %d", x1, x2, offset);
            result = x1 != x2;
            break;
        case 2:
            printf("if (%d > %d) : PC += %d", x1, x2, offset);
            result = x1 > x2;
            break;
        case 3:
            printf("if (%d <= %d) : PC += %d", x1, x2, offset);
            result = x1 <= x2;
            break;
        default:
            break;
    }

    if (result) {
        incrementPC(registers, offset);
    }
}

// parameters = [x1, x2, x3, isReverse]
void shiftLeft(int *registers, const int *executeParameters, const int *parameters) {
    printf("shiftLeft\n");

    int x1, x2, x3, isReverse;

    x1 = parameters[executeParameters[0] - 1];
    x2 = parameters[executeParameters[1] - 1];
    x3 = executeParameters[2];
    isReverse = executeParameters[3];

    unsigned int shift;

    if (x3 == -16) {
        shift = 16;
    } else {
        shift = x3;
        getValueFromRegister(registers, x2, &x2);
    }
    printf("ici\n");


    if (isReverse) {
        printf("$%d = %d >> %d", x1, x2, shift);
        setValueToRegister(registers, x1, x2 >> shift);
    } else {
        printf("$%d = %d << %d", x1, x2, shift);
        setValueToRegister(registers, x1, x2 << shift);
    }
}

// parameters = [x1, x2, x3, isSub, isImmediate]
void add(int *registers, const int *executeParameters, const int *parameters) {
    printf("add\n");

    int x1, x2, x3, isSub, isImmediate;

    x1 = parameters[executeParameters[0] - 1];
    getValueFromRegister(registers, parameters[executeParameters[1] - 1], &x2);
    x3 = parameters[executeParameters[2] - 1];
    isSub = executeParameters[3];
    isImmediate = executeParameters[4];


    if (!isImmediate) {
        getValueFromRegister(registers, x3, &x3);
    }

    x3 = (isSub) ? -x3 : x3;

    printf("$%d = %d + %d\n", x1, x2, x3);

    setValueToRegister(registers, x1, x2 + x3);
}

// parameters = [x1, x2, x3, operation]
void logical(int *registers, const int *executeParameters, const int *parameters) {
    printf("logical\n");

    int x1, x2, x3, operation;

    x1 = parameters[executeParameters[0] - 1];
    getValueFromRegister(registers, parameters[executeParameters[1] - 1], &x2);
    getValueFromRegister(registers, parameters[executeParameters[2] - 1], &x3);
    operation = executeParameters[3];

    int result = 0;

    switch (operation) {
        case 0:
            printf("$%d = %d & %d\n", x1, x2, x3);
            result = x2 & x3;
            break;
        case 1:
            printf("$%d = %d | %d\n", x1, x2, x3);
            result = x2 | x3;
            break;
        case 2:
            printf("$%d = %d ^ %d\n", x1, x2, x3);
            result = x2 ^ x3;
            break;
        case 3:
            printf("$%d = %d < %d\n", x1, x2, x3);
            result = x2 < x3;
            break;
        default:
            break;
    }

    setValueToRegister(registers, x1, result);
}

// parameters = [x, HIorLO]
void moveFrom(int *registers, const int *executeParameters, const int *parameters) {
    printf("moveFrom\n");

    int x, HIorLO;

    x = parameters[executeParameters[0] - 1];
    HIorLO = executeParameters[1];

    int result;

    if (HIorLO == 1) {
        getValueFromRegister(registers, HI, &result);
    } else {
        getValueFromRegister(registers, LO, &result);
    }

    printf("$%d = %d", x, result);
    setValueToRegister(registers, x, result);
}

// parameters = [x1, x2, offset]
void rotate(int *registers, const int *executeParameters, const int *parameters) {
    printf("rotate\n");

    int x1, x2, offset;

    x1 = parameters[executeParameters[0] - 1];
    getValueFromRegister(registers, parameters[executeParameters[1] - 1], &x2);
    offset = executeParameters[2] % 32;  // une rotation de 32 + n bits équivaut à une rotation de n bits

    // on va effectuer une rotation vers la gauche pour simplifier le code
    /*
     * Exemple pour rotate 0b10010 de 3 bits vers la droite : (exemple sur 5 bits pour simplifier)
     * upperNbits = 0b10010 & 0b11000 = 0b10000
     * lowerNbits = 0b10010 & 0b00111 = 0b00010
     * upperNbitsShifted = 0b10000 >> 3 = 0b00010
     * lowerNbitsShifted = 0b00010 << 2 = 0b01000
     * output = lowerNbitsShifted | upperNbitsShifted = 0b01010
     */

    int upperNbits = x2 & (int) getUpperBits(32 - offset, 32);
    int lowerNbits = x2 & (int) getLowerBits(offset);
    int upperNbitsShifted = upperNbits >> offset;
    int lowerNbitsShifted = lowerNbits << (32 - x2);

    printf("$%d = %d", x1, lowerNbitsShifted | upperNbitsShifted);
    setValueToRegister(registers, x1, lowerNbitsShifted | upperNbitsShifted);
}

// parameters = [x1, x2]
void divide(int *registers, const int *executeParameters, const int *parameters) {
    printf("divide\n");

    int x1, x2;

    getValueFromRegister(registers, parameters[executeParameters[0] - 1], &x1);
    getValueFromRegister(registers, parameters[executeParameters[1] - 1], &x2);

    printf("HI = %d %% %d", x1, x2);
    printf("LO = %d / %d", x1, x2);
    setValueToRegister(registers, HI, x1 % x2);
    setValueToRegister(registers, LO, x1 / x2);
}

// parameters = [x1, x2]
void multiply(int *registers, const int *executeParameters, const int *parameters) {
    printf("multiply\n");

    int x1, x2;

    getValueFromRegister(registers, parameters[executeParameters[0] - 1], &x1);
    getValueFromRegister(registers, parameters[executeParameters[1] - 1], &x2);

    long result;
    long lower32bits = getLowerBits(32);
    long upper32bits = getUpperBits(32, 64);

    result = (long) x1 * (long) x2;

    printf("HI = %d", (int) ((result & upper32bits) >> 32));
    printf("LO = %d", (int) (result & lower32bits));
    setValueToRegister(registers, LO, (int) (result & lower32bits));
    setValueToRegister(registers, HI, (int) ((result & upper32bits) >> 32));
}

// parameters = [x1, x2, x3, LorS]
void memory(int *registers, const int *executeParameters, const int *parameters) {
    printf("memory\n");

    int x1, x2, x3, LorS;

    x1 = parameters[executeParameters[0] - 1];
    x2 = parameters[executeParameters[1] - 1];
    getValueFromRegister(registers, parameters[executeParameters[2] - 1], &x3);
    LorS = executeParameters[3];






}
