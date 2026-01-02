#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpfr.h>

#include "naive.h"
#include "karatsuba.h"
#include "toom_cook.h"
#include "toom_4.h"
#include "naive_mpfr.h"
// Generate a random double in [-1,1]
double random_double() {
    return 2.0 * rand() / RAND_MAX - 1.0;
}
// Generate random polynomial
double *random_polynomial(int degree) {
    double *p = malloc((degree + 1) * sizeof(double));
    for (int i = 0; i <= degree; i++)
        p[i] = random_double();
    return p;
}
// Print polynomial
void print_polynomial(double *p, int degree) {
    for (int i = degree; i >= 0; i--) {
        printf("%.3f", p[i]);
        if (i > 1) printf("x^%d + ", i);
        else if (i == 1) printf("x + ");
    }
    printf("\n");
}


mpfr_t *mpfr_reference(double *A, int degA,double *B, int degB,mpfr_prec_t prec)
{
    mpfr_t *mpfr_A = init_mpfr_polynomial(degA, A, prec);
    mpfr_t *mpfr_B = init_mpfr_polynomial(degB, B, prec);

    mpfr_t *mpfr_C =
        naive_mpfr_multiplication(mpfr_A, degA + 1,
                                  mpfr_B, degB + 1);

    for (int i = 0; i <= degA; i++) mpfr_clear(mpfr_A[i]);
    for (int i = 0; i <= degB; i++) mpfr_clear(mpfr_B[i]);
    free(mpfr_A);
    free(mpfr_B);

    return mpfr_C;
}


double max_absolute_error(double *dbl, mpfr_t *mpfr, int degree) {
    double max_err = 0.0;
    for (int i = 0; i <= degree; i++) {
        double ref = mpfr_get_d(mpfr[i], MPFR_RNDN);
        double err = fabs(dbl[i] - ref);
        if (err > max_err) max_err = err;
    }
    return max_err;
}


void benchmark_algorithm(const char *name, double* (*func)(double*, int, double*, int, int), double *A, double *B, int deg, int k, mpfr_t *mpfr_ref)
{
    clock_t start = clock();
    double *C = func(A, deg, B, deg, k);
    clock_t end = clock();

    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double error = max_absolute_error(C, mpfr_ref, 2 * deg);

    printf("%-12s (k=%d) | time = %.6f s | max error = %.3e\n", name, k, time_sec, error);

    free(C);
}


int main() {
    srand(time(NULL));
    mpfr_prec_t precision = 256;

    int degrees[] = {8, 16, 32, 64};
    int n = sizeof(degrees) / sizeof(degrees[0]);

    printf("\nPolynomial Multiplication Accuracy Benchmark\n");
    printf("MPFR precision: %lu bits\n\n", precision);

    for (int i = 0; i < n; i++) {
        int deg = degrees[i];

        double *A = random_polynomial(deg);
        double *B = random_polynomial(deg);

        mpfr_t *mpfr_C = mpfr_reference(A, deg, B, deg, precision);

        printf("Degree %d\n", deg);
        printf("--------------------------------------------\n");

        benchmark_algorithm("Naive", naive_polynomial_multiplication, A, B, deg, 0, mpfr_C);

        for (int k = 2; k <= 4; k++)
            benchmark_algorithm("Karatsuba", karatsuba_polynomial_multiplication, A, B, deg, k, mpfr_C);

        for (int k = 2; k <= 4; k++)
            benchmark_algorithm("Toom-Cook", toom_cook_polynomial_multiplication, A, B, deg, k, mpfr_C);

        for (int k = 2; k <= 4; k++)
            benchmark_algorithm("Toom-4", toom_4_polynomial_multiplication, A, B, deg, k, mpfr_C);

        for (int j = 0; j <= 2 * deg; j++)
            mpfr_clear(mpfr_C[j]);

        free(mpfr_C);
        free(A);
        free(B);

        printf("\n");
    }

    return 0;
}
