#include "ExecuteFunctions.h"

ExecuteFunctions executeFunctions[10] = {
        jump,
        branch,
        shiftLeft,
        add,
        logical,
        moveFrom,
        rotate,
        divide,
        multiply,
        memory
};

//void initExecuteFunctions() {
//    executeFunctions[JUMP] = jump;
//    executeFunctions[BRANCH] = branch;
//    executeFunctions[SHIFT_LEFT] = shiftLeft;
//    executeFunctions[ADD] = add;
//    executeFunctions[LOGICAL] = logical;
//    executeFunctions[MOVE_FROM] = moveFrom;
//    executeFunctions[ROTATE] = rotate;
//    executeFunctions[DIVIDE] = divide;
//    executeFunctions[MULTIPLY] = multiply;
//    executeFunctions[MEMORY] = memory;
//}