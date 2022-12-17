#ifndef EXECUTE_FUNCTIONS_H
#define EXECUTE_FUNCTIONS_H

#include "execute.h"

typedef void (*ExecuteFunctions) (int*, int *);

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

#endif
