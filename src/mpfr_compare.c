//Soumyasree Chakraborty

#include <stdlib.h>
#include <math.h>

#include "mpfr_compare.h"
#include "naive_mpfr.h"

mpfr_t *mpfr_reference(double *A, int degA,double *B, int degB,mpfr_prec_t precision)
{
    mpfr_t *mpfr_A = init_mpfr_polynomial(degA, A, precision);
    mpfr_t *mpfr_B = init_mpfr_polynomial(degB, B, precision);

    mpfr_t *mpfr_C = naive_mpfr_multiplication(mpfr_A, degA + 1,mpfr_B, degB + 1);

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
