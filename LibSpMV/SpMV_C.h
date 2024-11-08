#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* row;
    int* col;
    double* value;
    int size; // Record the number of non-zero elements
} COO;

typedef struct {
    int* rowPtr;
    int* index;
    double* value;
    int numRows;
    int numNonZero; // Record the number of non-zero elements
} CSR;

COO convert2COO(double** matrix, int numRows, int numCols) {
    COO coo;
    coo.size = 0;

    // Allocated space for all non-zero elements (actually not needed)
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

    // Initialize row pointers
    csr.rowPtr = (int*)malloc((numRows + 1) * sizeof(int));
    csr.rowPtr[0] = 0;

    // Calculate the number of non-zero elements
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (matrix[i][j] != 0) {
                csr.numNonZero++;
            }
        }
        csr.rowPtr[i + 1] = csr.rowPtr[i]; // Initialize row pointers
    }

    // Allocate memory for values and column indices
    csr.value = (double*)malloc(csr.numNonZero * sizeof(double));
    csr.index = (int*)malloc(csr.numNonZero * sizeof(int));

    // Fill in values and column indices, and update row pointers
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

    // Convert row pointers to cumulative sums
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