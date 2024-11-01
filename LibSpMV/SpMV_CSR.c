#include <stdio.h>
#include <stdlib.h>

struct CSR {
    int* rowPtr;
    int* index;
    double* value;
};

void SpMV_CSR(struct CSR* csr, int m, double* x, double* result) {
    for (int i = 0; i < m; ++i) {
        result[i] = 0.0;
        for (int j = csr->rowPtr[i]; j < csr->rowPtr[i + 1]; ++j) {
            result[i] += csr->value[j] * x[csr->index[j]];
        }
    }
}

void demo_CSR() {
    struct CSR csr;
    int m = 3;
    int nnz = 7;

    csr.rowPtr = (int*)malloc((m + 1) * sizeof(int));
    csr.index = (int*)malloc(nnz * sizeof(int));
    csr.value = (double*)malloc(nnz * sizeof(double));

    csr.rowPtr[0] = 0; csr.rowPtr[1] = 2; csr.rowPtr[2] = 4; csr.rowPtr[3] = 7;
    csr.index[0] = 0; csr.index[1] = 1; csr.index[2] = 1; csr.index[3] = 2;
    csr.value[0] = 1.0; csr.value[1] = 2.0; 
    csr.value[2] = 3.0; csr.value[3] = 4.0; 
    csr.value[4] = 5.0; csr.value[5] = 6.0; 
    csr.value[6] = 7.0;

    double x[] = {1, 2, 3, 4};
    double* result = (double*)malloc(m * sizeof(double));

    SpMV_CSR(&csr, m, x, result);

    for (int i = 0; i < m; ++i) {
        printf("%f ", result[i]);
    }
    printf("\n");

    free(csr.rowPtr);
    free(csr.index);
    free(csr.value);
    free(result);
}

int main() {
    demo_CSR();
    return 0;
}
