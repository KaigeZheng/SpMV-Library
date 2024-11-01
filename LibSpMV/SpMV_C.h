#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* row;
    int* col;
    double* value;
    int size; // 记录非零元素的数量
} COO;

typedef struct {
    int* rowPtr;
    int* index;
    double* value;
    int numRows;
    int numNonZero; // 记录非零元素的数量
} CSR;

COO convert2COO(double** matrix, int numRows, int numCols) {
    COO coo;
    coo.size = 0;

    // 分配了所有非零元的空间(实际不需要)
    coo.row = (int*)malloc(numRows * numCols * sizeof(int));
    coo.col = (int*)malloc(numRows * numCols * sizeof(int));
    coo.value = (double*)malloc(numRows * numCols * sizeof(double));

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (matrix[i][j] != 0) {
                coo.row[coo.size] = i;
                coo.col[coo.size] = j;
                coo.value[coo.size] = matrix[i][j];
                coo.size++;
            }
        }
    }

    return coo;
}

void freeCOO(COO* coo) {
    free(coo->row);
    free(coo->col);
    free(coo->value);
}

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