#ifndef TOOM_COOK_H
#define TOOM_COOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "naive.h"

typedef enum {
    BASE_NAIVE = 0,
    BASE_KARATSUBA = 1
} base_algo;

double* toom_cook_polynomial_multiplication(double* A, int degA, double* B, int degB, int k, base_algo base);

#endif
