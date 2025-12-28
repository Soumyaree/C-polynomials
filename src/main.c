#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "naive.h"
#include "karatsuba.h"
#include "toom_cook.h"
#include "toom_4.h"
#include "naive_mpfr.h"

// Generate a random double in [-1,1]
double rand_double() {
    return ((double)rand() / RAND_MAX) * 2.0 - 1.0;
}

// Generate random polynomial
void random_poly(double *poly, int degree) {
    for (int i = 0; i <= degree; i++) {
        poly[i] = rand_double();
    }
}

// Print polynomial
void print_polynomial(double *poly, int degree) {
    for (int i = degree; i >= 0; i--) {
        if (poly[i] != 1 || i == 0)
            poly[i] != (int)poly[i] ? printf("%.2f", poly[i]) : printf("%.0f", poly[i]);
        if (i > 1) printf("x^%d", i);
        else if (i == 1) printf("x");
        if (i > 0) printf(" + ");
    }
    printf("\n");
}

// Run double-precision algorithm
double* run_algorithm_double(double *A, int degA, double *B, int degB,
                             double* (*func)(double*, int, double*, int, int),
                             const char* name, int k) {
    clock_t start = clock();
    double *C = func(A, degA, B, degB, k);
    clock_t end = clock();
    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%s", name);
    if (k > 0) printf(" (k=%d)", k);
    printf("\nResult: ");
    print_polynomial(C, degA + degB);
    printf("Time: %.8f seconds\n\n", time_sec);

    return C;
}

// Run MPFR algorithm
void run_algorithm_mpfr(double *A, int degA, double *B, int degB, mpfr_prec_t precision) {
    mpfr_t *mpfr_A = init_mpfr_polynomial(degA, A, precision);
    mpfr_t *mpfr_B = init_mpfr_polynomial(degB, B, precision);

    start = clock();
    mpfr_t *mpfr_C = naive_mpfr_multiplication(mpfr_A, degA + 1, mpfr_B, degB + 1);
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Result: ");
    print_mpfr_polynomial(mpfr_C, degA + degB);

    printf("Time taken: %.8f seconds\n", cpu_time_used);

    free_mpfr_polynomials(mpfr_A, degA, mpfr_B, degB, mpfr_C, degA + degB);

    return 0;
}