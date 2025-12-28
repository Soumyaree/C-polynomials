#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "naive.h"
#include "karatsuba.h"
#include "toom_cook.h"
#include "toom_4.h"
#include "naive_mpfr.h"

void print_polynomial(double*polynomial,  int degree) {
    for (int i = degree; i >= 0; i--) {
        // print decimals only if necessary
        if (polynomial[i] != 1 || i == 0) {
            polynomial[i] != (int)polynomial[i] ? printf("%.2f", polynomial[i]) : printf("%.0f", polynomial[i]);
        }
        if (i > 1) printf("x^%d", i);
        else if (i == 1) printf("x");
        if (i > 0) printf(" + ");
    }
    printf("\n");
}

void run_algorithm(double* A, int degA, double* B, int degB, 
                   double* (*multiplication_func)(double*, int, double*, int, int), 
                   const char* algorithm_name, int k) {
    clock_t start, end;
    double cpu_time_used;

    printf("%s", algorithm_name);
    printf("\n");
    if (k > 0) printf("For k = %d\n", k);
    start = clock();
    double *result = multiplication_func(A, degA, B, degB, k);
    end = clock();
    printf("Result: ");
    print_polynomial(result, degA + degB);
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %.8f seconds\n", cpu_time_used);
    free(result);
    printf("\n");
}

int main() {
    printf("MODEL Project\n");

    // defining variables
    double A[] = {0.5, 1, 4, 4, 1};
    int degA = 4;
    double B[] = {1, 3, 2.5, 1, 3};
    int degB = 4;
    
    // printing polynomials
    printf("Polynomials:\nA(x) = ");
    print_polynomial(A, degA);
    printf("B(x) = ");
    print_polynomial(B, degB);
    printf("\n");

    // Naive Polynomial Multiplication
    run_algorithm(A, degA, B, degB, naive_polynomial_multiplication, "Naive Polynomial Multiplication", 0);


    // Karatsuba Polynomial Multiplication
    for (int k = 2; k <= 4; k++) {
        run_algorithm(A, degA, B, degB, karatsuba_polynomial_multiplication, "Karatsuba Polynomial Multiplication", k);
    }

    printf("\n");

    // Toom-Cook Polynomial Multiplication
    for (int k = 2; k <= 4; k++) {
        run_algorithm(A, degA, B, degB, toom_cook_polynomial_multiplication, "Toom-Cook Polynomial Multiplication", k);
    }

    printf("\n");

    // Toom-4 Polynomial Multiplication
    for (int k = 2; k <= 4; k++) {
        run_algorithm(A, degA, B, degB, toom_4_polynomial_multiplication, "Toom-4 Polynomial Multiplication", k);
    }

    // Naive MPFR Multiplication
    printf("Naive MPFR Multiplication\n");
    mpfr_prec_t precision = 256;
    clock_t start, end;
    double cpu_time_used;

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