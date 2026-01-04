//Soumyasree Chakraborty

#include "naive_mpfr.h"

void _naive_mpfr_multiplication(mpfr_t* C, mpfr_t* A, int n, mpfr_t* B, int m) {
    int degC = n + m - 1;
    for (int i = 0; i < degC; i++) mpfr_set_d(C[i], 0.0, MPFR_RNDN);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mpfr_t temp;
            mpfr_init2(temp, mpfr_get_prec(A[i]) > mpfr_get_prec(B[j]) ? mpfr_get_prec(A[i]) : mpfr_get_prec(B[j]));
            mpfr_mul(temp, A[i], B[j], MPFR_RNDN);
            mpfr_add(C[i + j], C[i + j], temp, MPFR_RNDN);
            mpfr_clear(temp);
        }
    }
}

mpfr_t *naive_mpfr_multiplication(mpfr_t* A, int n, mpfr_t* B, int m) {
    mpfr_t *C = init_mpfr_polynomial(n + m - 1, NULL, mpfr_get_prec(A[0]));
    _naive_mpfr_multiplication(C, A, n, B, m);
    return C;
}

mpfr_t *init_mpfr_polynomial(int degree, double* coefficients, mpfr_prec_t precision) {
    mpfr_t *polynomial = (mpfr_t *)malloc((degree + 1) * sizeof(mpfr_t));
    for (int i = 0; i <= degree; i++) {
        mpfr_init2(polynomial[i], precision);
        if (coefficients != NULL) {
            mpfr_set_d(polynomial[i], coefficients[i], MPFR_RNDN);
        }
    }
    return polynomial;
}

void print_mpfr_polynomial(mpfr_t* polynomial, int degree) {
    for (int i = degree; i >= 0; i--) {
        // print decimals only if necessary
        double val = mpfr_get_d(polynomial[i], MPFR_RNDN);
        if (val == 0) {
            continue;
        }
        if (val != 1 || i == 0) {
            val != (int)val ? printf("%.2f", val) : printf("%.0f", val);
        }
        if (i > 1) printf("x^%d", i);
        else if (i == 1) printf("x");
        if (i > 0) printf(" + ");
    }
    printf("\n");
}

void free_mpfr_polynomials(mpfr_t* mpfr_A, int degA, mpfr_t* mpfr_B, int degB, mpfr_t* mpfr_C, int degC) {
    for (int i = 0; i <= degA; i++) {
        mpfr_clear(mpfr_A[i]);
    }
    for (int i = 0; i <= degB; i++) {
        mpfr_clear(mpfr_B[i]);
    }
    for (int i = 0; i <= degC; i++) {
        mpfr_clear(mpfr_C[i]);
    }
    free(mpfr_A);
    free(mpfr_B);
    free(mpfr_C);
}