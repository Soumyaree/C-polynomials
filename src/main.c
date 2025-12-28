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

    clock_t start = clock();
    mpfr_t *mpfr_C = naive_mpfr_multiplication(mpfr_A, degA + 1, mpfr_B, degB + 1);
    clock_t end = clock();

    printf("Naive MPFR Multiplication\nResult: ");
    print_mpfr_polynomial(mpfr_C, degA + degB);
    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %.8f seconds\n\n", time_sec);

    free_mpfr_polynomials(mpfr_A, degA, mpfr_B, degB, mpfr_C, degA + degB);
}

int main() {
    srand(time(NULL));
    printf("MODEL Project - Polynomial Multiplication Benchmark\n\n");

    int sizes[] = {8, 16, 32};
    int num_sizes = sizeof(sizes)/sizeof(sizes[0]);
    mpfr_prec_t mpfr_precision = 256;

    for (int s = 0; s < num_sizes; s++) {
        int degA = sizes[s];
        int degB = sizes[s];

        double *A = malloc((degA + 1) * sizeof(double));
        double *B = malloc((degB + 1) * sizeof(double));
        random_poly(A, degA);
        random_poly(B, degB);

        printf("Testing polynomials of degree %d and %d\n", degA, degB);
        printf("A(x) = "); print_polynomial(A, degA);
        printf("B(x) = "); print_polynomial(B, degB);
        printf("\n");

        // Naive
        double *C_naive = run_algorithm_double(A, degA, B, degB, naive_polynomial_multiplication, "Naive Double-Precision Multiplication", 0);
        free(C_naive);

        // Karatsuba best k
        int best_k = 2;
        double best_time = 1e9;
        for (int k = 2; k <= 4; k++) {
            double *C = run_algorithm_double(A, degA, B, degB, karatsuba_polynomial_multiplication, "Karatsuba Polynomial Multiplication", k);
            double t = (double)clock() / CLOCKS_PER_SEC; // approximation
            free(C);
        }
        printf("Best k for Karatsuba determined from above timings\n\n");

        // Toom-Cook best k
        for (int k = 2; k <= 4; k++) {
            double *C = run_algorithm_double(A, degA, B, degB, toom_cook_polynomial_multiplication, "Toom-Cook Polynomial Multiplication", k);
            free(C);
        }
        printf("Best k for Toom-Cook determined from above timings\n\n");

        // Toom-4 best k
        for (int k = 2; k <= 4; k++) {
            double *C = run_algorithm_double(A, degA, B, degB, toom_4_polynomial_multiplication, "Toom-4 Polynomial Multiplication", k);
            free(C);
        }
        printf("Best k for Toom-4 determined from above timings\n\n");

        // MPFR naive
        run_algorithm_mpfr(A, degA, B, degB, mpfr_precision);

        free(A);
        free(B);

        printf("------------------------------------------------------------\n\n");
    }

    return 0;
}
