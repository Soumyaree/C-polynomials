//Auriane Chevalier
//Abdullah Sheikh

#include "toom_cook.h"
#include "karatsuba.h"
#include "base_algo.h"

static void base_multiplication(double*C, double*A, int n, double*B, int m, int k, base_algo base) {
    if (base == BASE_KARATSUBA) {
        const int Kk=16;
        karatsuba_recursive(C, A, n, B, m, Kk);
    } else {
        naive_multiplication(C, A, n, B, m);
    }
}

static void toom3_recursive(double* C, double* A, int n, double* B, int m, int k, base_algo base) {
    // Base case
    if (n <= k || m <= k || n < 3 || m < 3) {
        base_multiplication(C, A, n, B, m, k, base);
        return;
    }

    // Split each polynomial into 3 parts
    int size = n > m ? n : m;
    int third = (size + 2) / 3;

    // add padding
    int padded = third * 3;
    double* Ap = (double*)calloc(padded, sizeof(double));
    double* Bp = (double*)calloc(padded, sizeof(double));
    memcpy(Ap, A, n * sizeof(double));
    memcpy(Bp, B, m * sizeof(double));

    // Split into parts
    double* a0 = Ap;
    double* a1 = Ap + third;
    double* a2 = Ap + 2 * third;
    double* b0 = Bp;
    double* b1 = Bp + third;
    double* b2 = Bp + 2 * third;

    // Allocate evaluation points (each has 'third' coefficients)
    double* p0 = (double*)calloc(third, sizeof(double));     // p(0) = a0
    double* p1 = (double*)calloc(third, sizeof(double));     // p(1) = a0 + a1 + a2
    double* pm1 = (double*)calloc(third, sizeof(double));    // p(-1) = a0 - a1 + a2
    double* pm2 = (double*)calloc(third, sizeof(double));    // p(-2) = a0 - 2*a1 + 4*a2
    double* pinf = (double*)calloc(third, sizeof(double));   // p(inf) = a2

    double* q0 = (double*)calloc(third, sizeof(double));
    double* q1 = (double*)calloc(third, sizeof(double));
    double* qm1 = (double*)calloc(third, sizeof(double));
    double* qm2 = (double*)calloc(third, sizeof(double));
    double* qinf = (double*)calloc(third, sizeof(double));

    // Evaluate at points: 0, 1, -1, -2
    for (int i = 0; i < third; i++) {
        p0[i] = a0[i];
        p1[i] = a0[i] + a1[i] + a2[i];
        pm1[i] = a0[i] - a1[i] + a2[i];
        pm2[i] = a0[i] - 2.0 * a1[i] + 4.0 * a2[i];
        pinf[i] = a2[i];

        q0[i] = b0[i];
        q1[i] = b0[i] + b1[i] + b2[i];
        qm1[i] = b0[i] - b1[i] + b2[i];
        qm2[i] = b0[i] - 2.0 * b1[i] + 4.0 * b2[i];
        qinf[i] = b2[i];
    }

    // Recursive multiplication at each point
    int rsize = 2 * third - 1;
    double* r0 = (double*)calloc(rsize, sizeof(double));
    double* r1 = (double*)calloc(rsize, sizeof(double));
    double* rm1 = (double*)calloc(rsize, sizeof(double));
    double* rm2 = (double*)calloc(rsize, sizeof(double));
    double* rinf = (double*)calloc(rsize, sizeof(double));

    toom3_recursive(r0, p0, third, q0, third, k, base);
    toom3_recursive(r1, p1, third, q1, third, k, base);
    toom3_recursive(rm1, pm1, third, qm1, third, k, base);
    toom3_recursive(rm2, pm2, third, qm2, third, k, base);
    toom3_recursive(rinf, pinf, third, qinf, third, k, base);

    double* w0 = (double*)calloc(rsize, sizeof(double));
    double* w1 = (double*)calloc(rsize, sizeof(double));
    double* w2 = (double*)calloc(rsize, sizeof(double));
    double* w3 = (double*)calloc(rsize, sizeof(double));
    double* w4 = (double*)calloc(rsize, sizeof(double));

    for (int i = 0; i < rsize; i++) {
        double v0 = r0[i];
        double v1 = r1[i];
        double vm1 = rm1[i];
        double vm2 = rm2[i];
        double vinf = rinf[i];

        w0[i] = v0;
        w4[i] = vinf;

        double t1 = (v1 + vm1) / 2.0 - v0 - vinf;
        double t2 = (v1 - vm1) / 2.0;
        double t3 = (vm2 - v0 - 4.0 * t1 - 16.0 * vinf) / (-2.0);

        w3[i] = (t3 - t2) / 3.0;
        w1[i] = t2 - w3[i];
        w2[i] = t1;
    }

    // Combine
    int degC = n + m - 1;
    for (int i = 0; i < degC; i++) C[i] = 0.0;

    for (int i = 0; i < rsize; i++) {
        if (i < degC) C[i] += w0[i];
        if (i + third < degC) C[i + third] += w1[i];
        if (i + 2 * third < degC) C[i + 2 * third] += w2[i];
        if (i + 3 * third < degC) C[i + 3 * third] += w3[i];
        if (i + 4 * third < degC) C[i + 4 * third] += w4[i];
    }


    free(Ap); free(Bp);
    free(p0); free(p1); free(pm1); free(pm2); free(pinf);
    free(q0); free(q1); free(qm1); free(qm2); free(qinf);
    free(r0); free(r1); free(rm1); free(rm2); free(rinf);
    free(w0); free(w1); free(w2); free(w3); free(w4);
}

double* toom_cook_polynomial_multiplication(double* A, int degA, double* B, int degB, int k, base_algo base) {
    int degC = degA + degB;
    double* C = (double*)calloc(degC + 1, sizeof(double));
    toom3_recursive(C, A, degA + 1, B, degB + 1, k, base);
    return C;
}
