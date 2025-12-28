#ifndef TOOM_4_H
#define TOOM_4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "naive.h"

double* toom_4_polynomial_multiplication(double* A, int degA, double* B, int degB, int k);

#endif // TOOM_4_H
