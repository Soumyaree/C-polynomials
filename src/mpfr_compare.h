#ifndef MPFR_COMPARE_H
#define MPFR_COMPARE_H

#include <mpfr.h>

mpfr_t *mpfr_reference(double *A, int degA, double *B, int degB, mpfr_prec_t precision);
double max_absolute_error(double *dbl, mpfr_t *mpfr, int degree);

#endif