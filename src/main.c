#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "naive.h"
#include "karatsuba.h"
#include "toom_cook.h"
#include "toom_4.h"
#include "mpfr_compare.h"

// Generate a random double in [-1,1]
static double random_double(void) {
    return 2.0 * rand() / RAND_MAX - 1.0;
}

static double *random_polynomial(int degree) {
    double *p = malloc((degree + 1) * sizeof(double));
    if (!p) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= degree; i++)
        p[i] = random_double();
    return p;
}


static void benchmark_algorithm(
    const char *name,
    double *(*func)(double *, int, double *, int, int),
    double *A, double *B,
    int degree, int k,
    mpfr_t *mpfr_ref
) {
    clock_t start = clock();
    double *C = func(A, degree, B, degree, k);
    clock_t end = clock();

    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double error = max_absolute_error(C, mpfr_ref, 2 * degree);

    printf("%-12s (k=%d) | time = %.6f s | max error = %.3e\n", name, k, time_sec, error);

    free(C);
}

int main(void) {
    srand((unsigned)time(NULL));

    /* MPFR reference precision */
    mpfr_prec_t precision = 256;

    /* Polynomial degrees to test */
    int degrees[] = {8, 16, 32, 64};
    int num_degrees = sizeof(degrees) / sizeof(degrees[0]);

    printf("\nPolynomial Multiplication Benchmark\n");
    printf("MPFR reference precision: %lu bits\n\n", precision);

    for (int i = 0; i < num_degrees; i++) {
        int deg = degrees[i];

        /* Generate random polynomials */
        double *A = random_polynomial(deg);
        double *B = random_polynomial(deg);

        /* Computing MPFR reference once */
        mpfr_t *mpfr_ref = mpfr_reference(A, deg, B, deg, precision);

        printf("Degree %d\n", deg);
        printf("--------------------------------------------\n");

        /* Naive */
        benchmark_algorithm(
            "Naive",
            naive_polynomial_multiplication,
            A, B, deg, 0,
            mpfr_ref
        );

        /* Karatsuba */
        for (int k = 2; k <= 4; k++) {
            benchmark_algorithm(
                "Karatsuba",
                karatsuba_polynomial_multiplication,
                A, B, deg, k,
                mpfr_ref
            );
        }

        /* Toom-Cook */
        for (int k = 2; k <= 4; k++) {
            benchmark_algorithm(
                "Toom-Cook",
                toom_cook_polynomial_multiplication,
                A, B, deg, k,
                mpfr_ref
            );
        }

        /* Toom-4 */
        for (int k = 2; k <= 4; k++) {
            benchmark_algorithm(
                "Toom-4",
                toom_4_polynomial_multiplication,
                A, B, deg, k,
                mpfr_ref
            );
        }

        /* Cleanup */
        for (int j = 0; j <= 2 * deg; j++)
            mpfr_clear(mpfr_ref[j]);
        free(mpfr_ref);
        free(A);
        free(B);

        printf("\n");
    }

    return 0;
}
