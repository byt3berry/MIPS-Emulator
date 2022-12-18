#include "execute.h"
//#include "Instruction.h"
#include "registers.h"
#include "constantes.h"
#include "utils.h"
#include "memory.h"
#include <stdlib.h>


//void execute(Instruction *instruction) {
//
//}

// parameters = [target, link, isRegister]
void jump(const int *executeParameters, const int *parameters) {
    printf("jump\n");

    int target, link, isRegister;

    target = executeParameters[0];
    link = executeParameters[1];
    isRegister = executeParameters[2];

    int PCupper = 0;
    int offset = 0;
    int PCvalue;
    getValueFromRegister(PC, &PCvalue);

    if (isRegister) {
        getValueFromRegister(parameters[target - 1], &target);
    } else if (link) {
        setValueToRegister(31, PCvalue);
        offset = 2;
    } else {
        PCupper = getPCupper(PCvalue);
        offset = 2;
    }

    printf("PC = %d | %d << %d\n", PCupper, target, offset);

    setValueToRegister(PC, PCupper | (target << offset));
}

// parameters = [x1, x2, condition, offset]
void branch(const int *executeParameters, const int *parameters) {
    printf("branch\n");

    int x1, x2, condition, offset;

    getValueFromRegister(parameters[executeParameters[0] - 1], &x1);
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);
    condition = executeParameters[2];
    offset = executeParameters[3];

    int result = 0;
    int PCvalue;
    getValueFromRegister(PC, &PCvalue);

    switch (condition) {
        case 0:
            printf("if (%d == %d) : PC += %d\n", x1, x2, offset);
            result = x1 == x2;
            break;
        case 1:
            printf("if (%d != %d) : PC += %d\n", x1, x2, offset);
            result = x1 != x2;
            break;
        case 2:
            printf("if (%d > %d) : PC += %d\n", x1, x2, offset);
            result = x1 > x2;
            break;
        case 3:
            printf("if (%d <= %d) : PC += %d\n", x1, x2, offset);
            result = x1 <= x2;
            break;
        default:
            break;
    }

    if (result) {
        incrementPC(offset);
    }
}

// parameters = [x1, x2, x3, isReverse]
void shiftLeft(const int *executeParameters, const int *parameters) {
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
        getValueFromRegister(x2, &x2);
    }
    printf("ici\n");


    if (isReverse) {
        printf("$%d = %d >> %d\n", x1, x2, shift);
        setValueToRegister(x1, x2 >> shift);
    } else {
        printf("$%d = %d << %d\n", x1, x2, shift);
        setValueToRegister(x1, x2 << shift);
    }
}

// parameters = [x1, x2, x3, isSub, isImmediate]
void add(const int *executeParameters, const int *parameters) {
    printf("add\n");

    int x1, x2, x3, isSub, isImmediate;

    x1 = parameters[executeParameters[0] - 1];
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);
    x3 = parameters[executeParameters[2] - 1];
    isSub = executeParameters[3];
    isImmediate = executeParameters[4];


    if (!isImmediate) {
        getValueFromRegister(x3, &x3);
    }

    x3 = (isSub) ? -x3 : x3;

    printf("$%d = %d + %d\n", x1, x2, x3);

    setValueToRegister(x1, x2 + x3);
}

// parameters = [x1, x2, x3, operation]
void logical(const int *executeParameters, const int *parameters) {
    printf("logical\n");

    int x1, x2, x3, operation;

    x1 = parameters[executeParameters[0] - 1];
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);
    getValueFromRegister(parameters[executeParameters[2] - 1], &x3);
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

    setValueToRegister(x1, result);
}

// parameters = [x, HIorLO]
void moveFrom(const int *executeParameters, const int *parameters) {
    printf("moveFrom\n");

    int x, HIorLO;

    x = parameters[executeParameters[0] - 1];
    HIorLO = executeParameters[1];

    int result;

    if (HIorLO == 1) {
        getValueFromRegister(HI, &result);
    } else {
        getValueFromRegister(LO, &result);
    }

    printf("$%d = %d\n", x, result);
    setValueToRegister(x, result);
}

// parameters = [x1, x2, offset]
void rotate(const int *executeParameters, const int *parameters) {
    printf("rotate\n");

    int x1, x2, offset;

    x1 = parameters[executeParameters[0] - 1];
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);
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

    printf("$%d = %d\n", x1, lowerNbitsShifted | upperNbitsShifted);
    setValueToRegister(x1, lowerNbitsShifted | upperNbitsShifted);
}

// parameters = [x1, x2]
void divide(const int *executeParameters, const int *parameters) {
    printf("divide\n");

    int x1, x2;

    getValueFromRegister(parameters[executeParameters[0] - 1], &x1);
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);

    printf("HI = %d %% %d\n", x1, x2);
    printf("LO = %d / %d\n", x1, x2);
    setValueToRegister(HI, x1 % x2);
    setValueToRegister(LO, x1 / x2);
}

// parameters = [x1, x2]
void multiply(const int *executeParameters, const int *parameters) {
    printf("multiply\n");

    int x1, x2;

    getValueFromRegister(parameters[executeParameters[0] - 1], &x1);
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);

    long result;
    long lower32bits = getLowerBits(32);
    long upper32bits = getUpperBits(32, 64);

    result = (long) x1 * (long) x2;

    printf("HI = %d\n", (int) ((result & upper32bits) >> 32));
    printf("LO = %d\n", (int) (result & lower32bits));
    setValueToRegister(LO, (int) (result & lower32bits));
    setValueToRegister(HI, (int) ((result & upper32bits) >> 32));
}

// parameters = [x1, offset, x2, LorS]
void memoryAccess(const int *executeParameters, const int *parameters) {
    printf("memory\n");

    int x1, offset, x2, LorS;

    x1 = parameters[executeParameters[0] - 1];
    offset = parameters[executeParameters[1] - 1];
    getValueFromRegister(parameters[executeParameters[2] - 1], &x2);
    LorS = executeParameters[3];

    int value;

    switch (LorS) {
        case 0:
            getValueFromMemory(x2 + offset, &value);
            setValueToRegister(x1, value);
            printf("$%d = %d\n", x1, value);
            break;
        case 1:
            getValueFromRegister(x1, &value);
            setValueToMemory(x2 + offset, value);
            printf("MEM[%d] = %d\n", x2 + offset, value);
            break;
        default:
            break;
    }


}
