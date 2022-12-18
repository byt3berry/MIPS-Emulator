#ifndef EXECUTE_FUNCTIONS_H
#define EXECUTE_FUNCTIONS_H

#include "execute.h"

typedef void (*ExecuteFunctions) (int*, const int *, const int *);

extern ExecuteFunctions executeFunctions[10];

#endif
