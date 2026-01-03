//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//#include <string.h>
//#include "toom_cook.h"
//
//void naive_multiplication(double* C, double* A, int n, double* B, int m);
//
//static inline double now_seconds(void) {
//#if defined(_WIN32) || defined(_WIN64)
//    return (double)clock() / (double)CLOCKS_PER_SEC;
//#else
//    struct timespec ts;
//    clock_gettime(CLOCK_MONOTONIC, &ts);
//    return (double)ts.tv_sec + 1e-9 * (double)ts.tv_nsec;
//#endif
//}
//
//static void fill_random(double* P, int n) {
//    for (int i = 0; i < n; i++) {
//        P[i] = 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
//    }
//}
//
//static int almost_equal_poly(const double* X, const double* Y, int n, double eps) {
//    for (int i = 0; i < n; i++) {
//        double diff = fabs(X[i] - Y[i]);
//        if (diff > eps) return 0;
//    }
//    return 1;
//}
//
//static void bench_naive_for_size(int N, int R) {
//    int sizeC = 2 * N - 1;
//
//    double* A = (double*)malloc(N * sizeof(double));
//    double* B = (double*)malloc(N * sizeof(double));
//    double* C  = (double*)malloc(sizeC * sizeof(double));
//    double* Ccheck = (double*)malloc(sizeC * sizeof(double));
//
//    if (!A || !B || !C || !Ccheck) {
//        fprintf(stderr, "alloc fail (N=%d)\n", N);
//        free(A); free(B); free(C); free(Ccheck);
//        exit(EXIT_FAILURE);
//    }
//
//    fill_random(A, N);
//    fill_random(B, N);
//    memset(Ccheck, 0, sizeC * sizeof(double));
//    naive_multiplication(Ccheck, A, N, B, N);
//    memset(C, 0, sizeC * sizeof(double));
//    naive_multiplication(C, A, N, B, N);
//    double t0 = now_seconds();
//    for (int r = 0; r < R; r++) {
//            memset(C, 0, sizeC * sizeof(double));
//    naive_multiplication(C, A, N, B, N);
//    }
//    double t1 = now_seconds();
//
//    double avg_ms = 1000.0 * (t1 - t0) / (double)R;
//    int ok = almost_equal_poly(C, Ccheck, sizeC, 1e-12);
//    printf("%d,%.6f%s\n", N, avg_ms, ok ? "" : ",ERROR");
//
//    free(A);
//    free(B);
//    free(C);
//    free(Ccheck);
//}
//
//
//int main(void) {
//    srand(0);
//
//    int sizes[] = {256, 512, 1024, 2048, 4096, 8192};
//    int nbs = sizeof(sizes) / sizeof(sizes[0]);
//
//    int R = 200;
//
//    for (int i = 0; i < nbs; i++) {
//        bench_naive_for_size(sizes[i], R);
//    }
//
//    return 0;
//}
