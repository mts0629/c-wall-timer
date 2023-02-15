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

// NxN matrix multiply: C = AB
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

    printf("%dx%d matmul time\n", N, N);

    for (int i = 0; i < 10; i++) {
        ts_get(&start);

        // Main processing
        matmul(A, B, C);

        ts_get(&end);

        ts_get_diff(&diff, &start, &end);

        printf("[%2d] %f[ms]\n", (i + 1), ts_get_time_as(&diff, TIME_SCALE_MS));

        ts_accumulate(&total, &diff);
    }

    printf("Total: %f[ms]\n", ts_get_time_as(&total, TIME_SCALE_MS));

    return 0;
}
