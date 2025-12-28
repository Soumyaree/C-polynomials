#ifndef NAIVE_MPFR_H
#define NAIVE_MPFR_H

#include <stdlib.h>
#include <stdio.h>
#include <mpfr.h>

void _naive_mpfr_multiplication(mpfr_t* C, mpfr_t* A, int n, mpfr_t* B, int m);

mpfr_t *naive_mpfr_multiplication(mpfr_t* A, int n, mpfr_t* B, int m);

mpfr_t *init_mpfr_polynomial(int degree, double* coefficients,  mpfr_prec_t precision);

void print_mpfr_polynomial(mpfr_t* polynomial, int degree);

void free_mpfr_polynomials(mpfr_t* mpfr_A, int degA, mpfr_t* mpfr_B, int degB, mpfr_t* mpfr_C, int degC);

#endif // NAIVE_MPFR_H