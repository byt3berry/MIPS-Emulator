#ifndef EXECUTE_H
#define EXECUTE_H

typedef int (*ExecuteFunctions) (const int *, const int *);

extern ExecuteFunctions executeFunctions[];

int jump(const int *, const int *);

int branch(const int *, const int *);

int shiftLeft(const int *, const int *);

int add(const int *, const int *);

int logical(const int *, const int *);

int moveFrom(const int *, const int *);

int rotate(const int *, const int *);

int divide(const int *, const int *);

int multiply(const int *, const int *);

int memoryAccess(const int *, const int *);

#endif


