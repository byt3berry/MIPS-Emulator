#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdio.h>


void decToBin(int, int, char *);

void binToHex(const char *, char *);

void replaceChar(char *, char, char);

void toUpperCase(char *);

void toLowerCase(char *);

void complementA2(char *);

long getLowerBits(int);

long getUpperBits(int, int);

#endif