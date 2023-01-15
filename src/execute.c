#include "execute.h"
#include "Instruction.h"
#include "registers.h"
#include "constantes.h"
#include "utils.h"
#include "memory.h"


ExecuteFunctions executeFunctions[11] = {
        jump,
        branch,
        shiftLeft,
        add,
        logical,
        moveFrom,
        rotate,
        divide,
        multiply,
        memoryAccess,
        nothing
};

// TODO: Interdire la modification de $0

// parameters = [target, link, isRegister]
void jump(const int *executeParameters, const int *parameters) {
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
        setValueToRegister(31, PCvalue + 8);
        target = parameters[target - 1] - 1;
        offset = 2;
    } else {
        PCupper = getPCupper(PCvalue);
        target = parameters[target - 1] - 1;
        offset = 2;
    }

    if (nextInstruction != NULL) {
        int instructionAssemble;
        getOutput(nextInstruction, &instructionAssemble);
        printf("%08X\n", instructionAssemble);
        printf("%s\n", nextInstruction->line);
        executeInstruction(nextInstruction);
    }


    setValueToRegister(PC, PCupper | (target << offset));
}

// parameters = [x1, x2, condition, offset]
void branch(const int *executeParameters, const int *parameters) {
    int x1, x2, condition, offset;

    getValueFromRegister(parameters[executeParameters[0] - 1], &x1);

    if (executeParameters[1] == 0) {
        x2 = executeParameters[1];
    } else {
        getValueFromRegister(parameters[executeParameters[1] - 1], &x2);
    }

    condition = executeParameters[2];
    offset = parameters[executeParameters[3] - 1];

    int result = 0;
    int PCvalue;
    getValueFromRegister(PC, &PCvalue);

    switch (condition) {
        case 0:
            result = x1 == x2;
            break;
        case 1:
            result = x1 != x2;
            break;
        case 2:
            result = x1 > x2;
            break;
        case 3:
            result = x1 <= x2;
            break;
        default:
            break;
    }


    if (nextInstruction != NULL) {
        int instructionAssemble;
        getOutput(nextInstruction, &instructionAssemble);
        printf("%08X\n", instructionAssemble);
        printf("%s\n", nextInstruction->line);
        executeInstruction(nextInstruction);
    }

    if (result) {
        incrementPC(offset);
    } else {
        incrementPC(1);
    }
}

// parameters = [x1, x2, x3, isReverse]
void shiftLeft(const int *executeParameters, const int *parameters) {
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

    if (isReverse) {
        setValueToRegister(x1, x2 >> shift);
    } else {
        setValueToRegister(x1, x2 << shift);
    }
}

// parameters = [x1, x2, x3, isSub, isImmediate]
void add(const int *executeParameters, const int *parameters) {
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

    setValueToRegister(x1, x2 + x3);
}

// parameters = [x1, x2, x3, operation]
void logical(const int *executeParameters, const int *parameters) {
    int x1, x2, x3, operation;

    x1 = parameters[executeParameters[0] - 1];
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);
    getValueFromRegister(parameters[executeParameters[2] - 1], &x3);
    operation = executeParameters[3];

    int result = 0;

    switch (operation) {
        case 0:
            result = x2 & x3;
            break;
        case 1:
            result = x2 | x3;
            break;
        case 2:
            result = x2 ^ x3;
            break;
        case 3:
            result = x2 < x3;
            break;
        default:
            break;
    }

    setValueToRegister(x1, result);
}

// parameters = [x, HIorLO]
void moveFrom(const int *executeParameters, const int *parameters) {
    int x, HIorLO;

    x = parameters[executeParameters[0] - 1];
    HIorLO = executeParameters[1];

    int result;

    if (HIorLO == 1) {
        getValueFromRegister(HI, &result);
    } else {
        getValueFromRegister(LO, &result);
    }

    setValueToRegister(x, result);
}

// parameters = [x1, x2, offset]
void rotate(const int *executeParameters, const int *parameters) {
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

    setValueToRegister(x1, lowerNbitsShifted | upperNbitsShifted);
}

// parameters = [x1, x2]
void divide(const int *executeParameters, const int *parameters) {
    int x1, x2;

    getValueFromRegister(parameters[executeParameters[0] - 1], &x1);
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);

    setValueToRegister(HI, x1 % x2);
    setValueToRegister(LO, x1 / x2);
}

// parameters = [x1, x2]
void multiply(const int *executeParameters, const int *parameters) {
    int x1, x2;

    getValueFromRegister(parameters[executeParameters[0] - 1], &x1);
    getValueFromRegister(parameters[executeParameters[1] - 1], &x2);

    long result;
    long lower32bits = getLowerBits(32);
    long upper32bits = getUpperBits(32, 64);

    result = (long) x1 * (long) x2;

    setValueToRegister(LO, (int) (result & lower32bits));
    setValueToRegister(HI, (int) ((result & upper32bits) >> 32));
}

// parameters = [x1, offset, x2, LorS]
void memoryAccess(const int *executeParameters, const int *parameters) {
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
            break;
        case 1:
            getValueFromRegister(x1, &value);
            setValueToMemory(x2 + offset, value);
            break;
        default:
            break;
    }
}

// parameters = [rien]
void nothing(const int *executeParameters, const int *parameters) {
    int rien = executeParameters[parameters[0]];
    incrementPC(rien);
}
