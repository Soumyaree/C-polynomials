#include "naive.h"

void naive_multiplication(double* C, double* A, int n, double* B, int m) {
    int degC = n + m - 1;
    for (int i = 0; i < degC; i++) C[i] = 0.0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            C[i + j] += A[i] * B[j];
}

double *naive_polynomial_multiplication(double *A, int m, double *B, int n, int k) {
    // k is unused in naive multiplication
    double *result = (double *)calloc(m + n - 1, sizeof(double));
    naive_multiplication(result, A, m, B, n);
    return result;
}
