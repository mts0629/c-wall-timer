/**
 * sample.c
 *
 * Measure calculation time of matrix multiplication
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ts_timer.h"

// Row/column size
#define N 512

// Randomize source matrix with [0, 1]
void randomize(double *array, const size_t n) {
    for (int i = 0; i < n; i++) {
        array[i] = (double)rand() / RAND_MAX;
    }
}

// NxN matrix multiplication: C = AB
void matmul(const double A[N * N], const double B[N * N], double C[N * N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double mac = 0;
            for (int k = 0; k < N; k++) {
                mac += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = mac;
        }
    }
}

// Num of iterations
#define ITER 10

int main(void) {
    // Matrices
    double A[N * N];
    double B[N * N];
    double C[N * N];

    // Initialize
    srand(time(NULL));
    randomize(A, (N * N));
    randomize(B, (N * N));
    randomize(C, (N * N));

    struct timespec start, end, diff;
    struct timespec total = { 0 };
    struct timespec avg;

    printf("%dx%d matmul (%d times)\n", N, N, ITER) ;

    for (int i = 0; i < ITER; i++) {
        ts_get(&start);

        // Main processing
        matmul(A, B, C);

        ts_get(&end);

        ts_get_diff(&diff, &start, &end);

        printf("[%2d] %f[ms]\n", (i + 1), ts_get_time_as(&diff, TIME_SCALE_MS));

        ts_accumulate(&total, &diff);
    }

    // Get average from the total
    ts_div(&avg, &total, ITER);

    printf("--------------------\n");
    printf("Total: %f[ms]\n", ts_get_time_as(&total, TIME_SCALE_MS));
    printf("Avg. : %f[ms]\n", ts_get_time_as(&avg, TIME_SCALE_MS));

    return 0;
}
