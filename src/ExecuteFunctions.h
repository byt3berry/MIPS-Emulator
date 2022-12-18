#ifndef EXECUTE_FUNCTIONS_H
#define EXECUTE_FUNCTIONS_H

#include "execute.h"

typedef void (*ExecuteFunctions) (const int *, const int *);

extern ExecuteFunctions executeFunctions[];

#endif
