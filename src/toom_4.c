#include "toom_4.h"

static void toom4_recursive(double* C, double* A, int n, double* B, int m, int k) {
    // Base case
    if (n <= k || m <= k || n < 4 || m < 4) {
        naive_multiplication(C, A, n, B, m);
        return;
    }

    int size = n > m ? n : m;
    int quarter = (size + 3) / 4;

    // padding
    int padded = quarter * 4;
    double* Ap = (double*)calloc(padded, sizeof(double));
    double* Bp = (double*)calloc(padded, sizeof(double));
    memcpy(Ap, A, n * sizeof(double));
    memcpy(Bp, B, m * sizeof(double));

    // split
    double* a0 = Ap;
    double* a1 = Ap + quarter;
    double* a2 = Ap + 2 * quarter;
    double* a3 = Ap + 3 * quarter;
    double* b0 = Bp;
    double* b1 = Bp + quarter;
    double* b2 = Bp + 2 * quarter;
    double* b3 = Bp + 3 * quarter;
    
    double* p0 = (double*)calloc(quarter, sizeof(double));      // p(0) = a0
    double* p1 = (double*)calloc(quarter, sizeof(double));      // p(1) = a0 + a1 + a2 + a3
    double* pm1 = (double*)calloc(quarter, sizeof(double));     // p(-1) = a0 - a1 + a2 - a3
    double* p2 = (double*)calloc(quarter, sizeof(double));      // p(2) = a0 + 2a1 + 4a2 + 8a3
    double* pm2 = (double*)calloc(quarter, sizeof(double));     // p(-2) = a0 - 2a1 + 4a2 - 8a3
    double* phalf = (double*)calloc(quarter, sizeof(double));   
    double* pinf = (double*)calloc(quarter, sizeof(double));    

    double* q0 = (double*)calloc(quarter, sizeof(double));
    double* q1 = (double*)calloc(quarter, sizeof(double));
    double* qm1 = (double*)calloc(quarter, sizeof(double));
    double* q2 = (double*)calloc(quarter, sizeof(double));
    double* qm2 = (double*)calloc(quarter, sizeof(double));
    double* qhalf = (double*)calloc(quarter, sizeof(double));
    double* qinf = (double*)calloc(quarter, sizeof(double));

    for (int i = 0; i < quarter; i++) {
        p0[i] = a0[i];
        p1[i] = a0[i] + a1[i] + a2[i] + a3[i];
        pm1[i] = a0[i] - a1[i] + a2[i] - a3[i];
        p2[i] = a0[i] + 2.0 * a1[i] + 4.0 * a2[i] + 8.0 * a3[i];
        pm2[i] = a0[i] - 2.0 * a1[i] + 4.0 * a2[i] - 8.0 * a3[i];
        phalf[i] = 8.0 * a0[i] + 4.0 * a1[i] + 2.0 * a2[i] + a3[i];
        pinf[i] = a3[i];

        q0[i] = b0[i];
        q1[i] = b0[i] + b1[i] + b2[i] + b3[i];
        qm1[i] = b0[i] - b1[i] + b2[i] - b3[i];
        q2[i] = b0[i] + 2.0 * b1[i] + 4.0 * b2[i] + 8.0 * b3[i];
        qm2[i] = b0[i] - 2.0 * b1[i] + 4.0 * b2[i] - 8.0 * b3[i];
        qhalf[i] = 8.0 * b0[i] + 4.0 * b1[i] + 2.0 * b2[i] + b3[i];
        qinf[i] = b3[i];
    }

    int rsize = 2 * quarter - 1;
    double* r0 = (double*)calloc(rsize, sizeof(double));
    double* r1 = (double*)calloc(rsize, sizeof(double));
    double* rm1 = (double*)calloc(rsize, sizeof(double));
    double* r2 = (double*)calloc(rsize, sizeof(double));
    double* rm2 = (double*)calloc(rsize, sizeof(double));
    double* rhalf = (double*)calloc(rsize, sizeof(double));
    double* rinf = (double*)calloc(rsize, sizeof(double));

    toom4_recursive(r0, p0, quarter, q0, quarter, k);
    toom4_recursive(r1, p1, quarter, q1, quarter, k);
    toom4_recursive(rm1, pm1, quarter, qm1, quarter, k);
    toom4_recursive(r2, p2, quarter, q2, quarter, k);
    toom4_recursive(rm2, pm2, quarter, qm2, quarter, k);
    toom4_recursive(rhalf, phalf, quarter, qhalf, quarter, k);
    toom4_recursive(rinf, pinf, quarter, qinf, quarter, k);

    double* w0 = (double*)calloc(rsize, sizeof(double));
    double* w1 = (double*)calloc(rsize, sizeof(double));
    double* w2 = (double*)calloc(rsize, sizeof(double));
    double* w3 = (double*)calloc(rsize, sizeof(double));
    double* w4 = (double*)calloc(rsize, sizeof(double));
    double* w5 = (double*)calloc(rsize, sizeof(double));
    double* w6 = (double*)calloc(rsize, sizeof(double));

    for (int i = 0; i < rsize; i++) {
        double v0 = r0[i];
        double v1 = r1[i];
        double vm1 = rm1[i];
        double v2 = r2[i];
        double vm2 = rm2[i];
        double vhalf = rhalf[i];
        double vinf = rinf[i];

        w0[i] = v0;
        w6[i] = vinf;

        double s1 = (v1 + vm1) / 2.0;            // w0 + w2 + w4 + w6
        double d1 = (v1 - vm1) / 2.0;            // w1 + w3 + w5
        double s2 = (v2 + vm2) / 2.0;            // w0 + 4w2 + 16w4 + 64w6
        double d2 = (v2 - vm2) / 4.0;            // w1 + 4w3 + 16w5
        double e1 = s1 - v0 - vinf;              // w2 + w4
        double e2 = s2 - v0 - 64.0 * vinf;       // 4w2 + 16w4

        w4[i] = (e2 - 4.0 * e1) / 12.0;
        w2[i] = e1 - w4[i];

        double o1 = d1;
        double o2 = d2;
        double o3 = (vhalf - 64.0 * w0[i] - 16.0 * w2[i] - 4.0 * w4[i] - w6[i]) / 2.0;

        w5[i] = (o3 + 4.0 * o2 - 20.0 * o1) / 45.0;
        w1[i] = w5[i] + (o3 - o2) / 15.0;
        w3[i] = o1 - w1[i] - w5[i];
    }

    int degC = n + m - 1;
    for (int i = 0; i < degC; i++) C[i] = 0.0;

    for (int i = 0; i < rsize; i++) {
        if (i < degC) C[i] += w0[i];
        if (i + quarter < degC) C[i + quarter] += w1[i];
        if (i + 2 * quarter < degC) C[i + 2 * quarter] += w2[i];
        if (i + 3 * quarter < degC) C[i + 3 * quarter] += w3[i];
        if (i + 4 * quarter < degC) C[i + 4 * quarter] += w4[i];
        if (i + 5 * quarter < degC) C[i + 5 * quarter] += w5[i];
        if (i + 6 * quarter < degC) C[i + 6 * quarter] += w6[i];
    }

    free(Ap); free(Bp);
    free(p0); free(p1); free(pm1); free(p2); free(pm2); free(phalf); free(pinf);
    free(q0); free(q1); free(qm1); free(q2); free(qm2); free(qhalf); free(qinf);
    free(r0); free(r1); free(rm1); free(r2); free(rm2); free(rhalf); free(rinf);
    free(w0); free(w1); free(w2); free(w3); free(w4); free(w5); free(w6);
}

double* toom_4_polynomial_multiplication(double* A, int degA, double* B, int degB, int k, base_algo base) {
    int degC = degA + degB;
    double* C = (double*)calloc(degC + 1, sizeof(double));
    toom4_recursive(C, A, degA + 1, B, degB + 1, k);
    return C;
}
