#include <stdio.h>
#include <stdlib.h>

void SpMV_2D(double** A, int m, int n, double* x, double* result) {
    for (int i = 0; i < m; ++i) {
        result[i] = 0.0;
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * x[j];
        }
    }
}

void demo_2D() {
    int m = 3, n = 3;
    
    double** A = (double**)malloc(m * sizeof(double*));
    for (int i = 0; i < m; ++i) {
        A[i] = (double*)malloc(n * sizeof(double));
    }

    A[0][0] = 1; A[0][1] = 0; A[0][2] = 1;
    A[1][0] = 0; A[1][1] = 1; A[1][2] = 0;
    A[2][0] = 0; A[2][1] = 0; A[2][2] = 1;

    double x[] = {1, 2, 3};
    double* result = (double*)malloc(m * sizeof(double)); // Dynamically allocate the result vector

    SpMV_2D(A, m, n, x, result);

    for (int i = 0; i < m; ++i) {
        printf("%f ", result[i]);
    }
    printf("\n");

    for (int i = 0; i < m; ++i) {
        free(A[i]);
    }
    free(A);
    free(result);
}

int main() {
    demo_2D();
    return 0;
}
