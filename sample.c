#include <stdio.h>
#include <stdlib.h>

#include "tm.h"

static void init_array_random(double *array, const size_t n) {
    for (int i = 0; i < n; i++) {
        array[i] = (double)rand() / RAND_MAX;
    }
}

#define N 512

int main(void) {
    double A[N * N];
    double B[N * N];
    double C[N * N];

    // Initialize matrices
    srand(time(NULL));
    init_array_random(A, (N * N));
    init_array_random(B, (N * N));
    init_array_random(C, (N * N));

    tm_span span;
    tm_start(&span);    // Start measurement
    // Matmul
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double mac = 0;
            for (int k = 0; k < N; k++) {
                mac += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = mac;
        }
    }
    tm_end(&span);      // Stop measurement

    // Get elapsed time in milliseconds
    printf("%f[ms]\n", tm_get_span_timescale(&span, TIMESCALE_MS));

    return 0;
}
