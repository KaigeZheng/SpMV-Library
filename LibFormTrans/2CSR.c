#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* rowPtr;
    int* index;
    double* value;
    int numRows;
    int numNonZero; // 记录非零元素的数量
} CSR;

CSR convert2CSR(double** matrix, int numRows, int numCols) {
    CSR csr;
    csr.numRows = numRows;
    csr.numNonZero = 0;

    // 初始化行指针
    csr.rowPtr = (int*)malloc((numRows + 1) * sizeof(int));
    csr.rowPtr[0] = 0;

    // 计算非零元素数量
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (matrix[i][j] != 0) {
                csr.numNonZero++;
            }
        }
        csr.rowPtr[i + 1] = csr.rowPtr[i]; // 初始化行指针
    }

    // 为值和列索引分配内存
    csr.value = (double*)malloc(csr.numNonZero * sizeof(double));
    csr.index = (int*)malloc(csr.numNonZero * sizeof(int));

    // 填充值和列索引，并更新行指针
    int idx = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (matrix[i][j] != 0) {
                csr.value[idx] = matrix[i][j];
                csr.index[idx] = j;
                idx++;
                csr.rowPtr[i + 1]++;
            }
        }
    }

    // 将行指针转换为累计和
    for (int i = 1; i <= numRows; ++i) {
        csr.rowPtr[i] += csr.rowPtr[i - 1];
    }

    return csr;
}

void freeCSR(CSR* csr) {
    free(csr->rowPtr);
    free(csr->index);
    free(csr->value);
}

void demo2CSR() {
    int numRows = 3, numCols = 3;

    double** matrix = (double**)malloc(numRows * sizeof(double*));
    for (int i = 0; i < numRows; i++) {
        matrix[i] = (double*)malloc(numCols * sizeof(double));
    }

    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0;
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 3;

    CSR csr = convert2CSR(matrix, numRows, numCols);

    printf("Row Pointer: ");
    for (int i = 0; i <= csr.numRows; i++) {
        printf("%d ", csr.rowPtr[i]);
    }
    printf("\nColumn Index: ");
    for (int i = 0; i < csr.numNonZero; i++) {
        printf("%d ", csr.index[i]);
    }
    printf("\nValues: ");
    for (int i = 0; i < csr.numNonZero; i++) {
        printf("%.2f ", csr.value[i]);
    }
    printf("\n");

    // 释放内存
    freeCSR(&csr);
    for (int i = 0; i < numRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    demo2CSR();
    return 0;
}
