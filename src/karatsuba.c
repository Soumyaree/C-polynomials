//Soumyasree Chakraborty

#include "karatsuba.h"
#include "naive.h"
#include <stdlib.h>
#include <string.h>

void karatsuba_recursive(double* C, double* A, int n, double* B, int m, int k) {
    if (n <= k || m <= k) {
        naive_multiplication(C, A, n, B, m);
        return;
    }

    int size = n > m ? n : m;
    int mid = size / 2;

    int n0 = mid < n ? mid : n;
    int n1 = n - n0;
    int m0 = mid < m ? mid : m;
    int m1 = m - m0;

    double* A0 = (double*)calloc(n0, sizeof(double));
    double* A1 = (double*)calloc(n1, sizeof(double));
    double* B0 = (double*)calloc(m0, sizeof(double));
    double* B1 = (double*)calloc(m1, sizeof(double));

    memcpy(A0, A, n0 * sizeof(double));
    if (n1 > 0) memcpy(A1, A + n0, n1 * sizeof(double));
    memcpy(B0, B, m0 * sizeof(double));
    if (m1 > 0) memcpy(B1, B + m0, m1 * sizeof(double));

    int maxSum = n1 > n0 ? n1 : n0;
    if (m1 > m0) maxSum = m1 > maxSum ? m1 : maxSum;

    int size0 = n0 + m0 - 1;
    int size2 = n1 + m1 - 1;
    int size1 = 2*maxSum - 1;

    double* Z0 = (double*)calloc(size0, sizeof(double));
    double* Z2 = (double*)calloc(size2, sizeof(double));
    double* Z1 = (double*)calloc(size1, sizeof(double));

    karatsuba_recursive(Z0, A0, n0, B0, m0, k);
    karatsuba_recursive(Z2, A1, n1, B1, m1, k);

    double* ASum = (double*)calloc(maxSum, sizeof(double));
    double* BSum = (double*)calloc(maxSum, sizeof(double));
    for (int i = 0; i < maxSum; i++) {
        double aVal = (i < n0 ? A0[i] : 0.0) + (i < n1 ? A1[i] : 0.0);
        double bVal = (i < m0 ? B0[i] : 0.0) + (i < m1 ? B1[i] : 0.0);
        ASum[i] = aVal;
        BSum[i] = bVal;
    }

    karatsuba_recursive(Z1, ASum, maxSum, BSum, maxSum, k);

    int degC = n + m - 1;
    for (int i = 0; i < degC; i++) C[i] = 0.0;

    for (int i = 0; i < size0; i++) C[i] += Z0[i];
    for (int i = 0; i < size2; i++) C[i + mid * 2] += Z2[i];
    for (int i = 0; i < size1; i++) {
        double z0Val = i < size0 ? Z0[i] : 0.0;
        double z2Val = i < size2 ? Z2[i] : 0.0;
        C[i + mid] += Z1[i] - z0Val - z2Val;
    }

    free(A0); free(A1); free(B0); free(B1);
    free(Z0); free(Z1); free(Z2);
    free(ASum); free(BSum);
}

double *karatsuba_polynomial_multiplication(double* A, int degA, double* B, int degB, int k) {
    int degC = degA + degB;
    double* C = (double*)calloc(degC + 1, sizeof(double));
    karatsuba_recursive(C, A, degA + 1, B, degB + 1, k);
    return C;
}
