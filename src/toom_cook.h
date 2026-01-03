#ifndef TOOM_COOK_H
#define TOOM_COOK_H

#include <stdio.h>
#include <stdlib.h>
#include "naive.h"
#include "base_algo.h"

double* toom_cook_polynomial_multiplication(
    double* A, int degA,
    double* B, int degB,
    int k,
    base_algo base
);

#endif
