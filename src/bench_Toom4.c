#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "toom_4.h"

void naive_multiplication(double* C, double* A, int n, double* B, int m);
double* toom_4_polynomial_multiplication(double* A, int degA, double* B, int degB, int k, base_algo base);

static inline double now_seconds(void) {
#if defined(_WIN32) || defined(_WIN64)
   return (double)clock() / (double)CLOCKS_PER_SEC;
#else
   struct timespec ts;
   clock_gettime(CLOCK_MONOTONIC, &ts);
   return (double)ts.tv_sec + 1e-9 * (double)ts.tv_nsec;
#endif
}

static void fill_random(double* P, int n) {
   for (int i = 0; i < n; i++) {
       P[i] = 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
   }
}

static int almost_equal_poly(const double* X, const double* Y, int n, double eps) {
   for (int i = 0; i < n; i++) {
       double diff = fabs(X[i] - Y[i]);
       if (diff > eps) return 0;
   }
   return 1;
}

static void bench_k_for_size(int N, const int* ks, int nbk, int R) {
   int degA = N - 1, degB = N - 1;
   int degC = degA + degB;
   int sizeC = degC + 1;

   double* A = (double*)malloc(N * sizeof(double));
   double* B = (double*)malloc(N * sizeof(double));
   double* Cref = (double*)calloc(sizeC, sizeof(double));

   fill_random(A, N);
   fill_random(B, N);


   naive_multiplication(Cref, A, N, B, N);

   printf("N=%d\n", N);
   printf("k,time_avg_ms\n");

   for (int idx = 0; idx < nbk; idx++) {
       int k = ks[idx];

       double* Cw = toom_4_polynomial_multiplication(A, degA, B, degB, k, NAIVE_BASE);
       free(Cw);

       double t0 = now_seconds();
       for (int r = 0; r < R; r++) {
           double* C = toom_4_polynomial_multiplication(A, degA, B, degB, k, NAIVE_BASE);
           free(C);
       }
       double t1 = now_seconds();
       double avg_ms = 1000.0 * (t1 - t0) / (double)R;

       double* Ccheck = toom_4_polynomial_multiplication(A, degA, B, degB, k, NAIVE_BASE);
       int ok = almost_equal_poly(Ccheck, Cref, sizeC, 1e-7);
       free(Ccheck);

       printf("%d,%.6f%s\n", k, avg_ms, ok ? "" : ",ERROR");
   }
   printf("\n");

   free(A); free(B); free(Cref);
}

static void correctness_tests(void) {
   int sizes[] = {16, 32, 64, 128, 256};
   int ks[]={4, 8, 16, 32, 64, 128};

   int T = 20; //number of random draw of polynoms

   int nbs = sizeof(sizes) / sizeof(sizes[0]);
   int nbk = sizeof(ks) / sizeof(ks[0]);

   printf("=== Correctness test ===\n");

   for (int s=0; s<nbs; s++) {
       int N=sizes[s];
       int degA = N - 1, degB= N-1;
       int sizeC = 2*N-1;

       double *A = malloc(N*sizeof(double));
       double *B = malloc(N*sizeof(double));
       double *Cref = malloc(sizeC * sizeof(double));
       for (int kidx = 0; kidx<nbk; kidx++) {
           int k = ks[kidx];
           for (int t=0; t<T; t++) {

               fill_random(A, N);
               fill_random(B, N);
               memset(Cref, 0, sizeC * sizeof(double));
               naive_multiplication(Cref, A, N, B, N);
               double* C = toom_4_polynomial_multiplication(A, degA, B, degB, k, NAIVE_BASE);
               if (!almost_equal_poly(C, Cref, sizeC, 1e-7)) {
                   printf("ERROR: N=%d, k=%d\n", N, k);
                   free(C);
                   goto cleanup;
               }
           free(C);
           }
       }

       printf("Correct for N = %d\n", N);
   cleanup:
       free(A);
       free(B);
       free(Cref);
   }

   printf("Correctness tests finished\n\n");
}

static void base_case (int k, int min_deg, int max_deg, int step_deg, int repetition) {
   printf("deg,k,time_naive, time_karatsuba, winner\n");
   for (int deg = min_deg; deg <= max_deg; deg += step_deg) {
       int n = deg + 1;
       int m = deg + 1;
       double *A = (double*)malloc(n * sizeof(double));
       double *B = (double*)malloc(m * sizeof(double));
       if (!A || !B) {
               fprintf(stderr, "alloc fail\n");
               free(A);
               free(B);
               exit(1);
       }

       fill_random(A,n);
       fill_random(B,m);

       double average_time[2]={0.0, 0.0};
       for (int base = NAIVE_BASE; base <= BASE_KARATSUBA; base++) {
               double *Cw = toom_4_polynomial_multiplication(A, deg, B, deg, k, (base_algo)base);
               free(Cw);

               double t0=now_seconds();
               for (int r = 0; r < repetition; r++){
                       double *C = toom_4_polynomial_multiplication(A, deg, B, deg, k, (base_algo)base);
                       free(C);
               }
               double t1=now_seconds();
               average_time[base] = 1000.0*(t1 - t0) / repetition;

       }
       const char* winner = (average_time[NAIVE_BASE] <= average_time[BASE_KARATSUBA]) ? "naive" : "karatsuba";
       printf("%d,%d,naive: %.9f, karatsuba: %.9f, winner : %s\n", deg, k, average_time[NAIVE_BASE], average_time[BASE_KARATSUBA], winner);

       free(A);
       free(B);
   }
}

int main(void) {
   srand(0);

   correctness_tests();

   int ks[] = {4, 8, 16, 32, 64, 128};
   int nbk = sizeof(ks) / sizeof(ks[0]);

   int sizes[] = {256, 512, 1024, 2048, 4096, 8192};
   int nbs = sizeof(sizes) / sizeof(sizes[0]);

   int R = 200;

   for (int i = 0; i < nbs; i++) {
       bench_k_for_size(sizes[i], ks, nbk, R);
   }

   int k = 64;
   int min_deg=64;
   int max_deg=256;
   int step_deg=16;
   int repetition=2000;

   base_case(k, min_deg, max_deg, step_deg, repetition);
   return 0;
}
