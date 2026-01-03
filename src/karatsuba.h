#ifndef KARATSUBA_H
#define KARATSUBA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "naive.h"

void karatsuba_recursive(double*C, double*A, int n, double*B, int m, int k);

double *karatsuba_polynomial_multiplication(double* A, int degA, double* B, int degB, int k);

#endif
