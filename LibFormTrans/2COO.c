#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* row;
    int* col;
    double* value;
    int size; // 记录非零元素的数量
} COO;

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

void demo2COO() {
    int numRows = 3, numCols = 3;

    double** matrix = (double**)malloc(numRows * sizeof(double*));
    for (int i = 0; i < numRows; i++) {
        matrix[i] = (double*)malloc(numCols * sizeof(double));
    }

    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0;
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 3;

    COO coo = convert2COO(matrix, numRows, numCols);

    printf("Row: ");
    for (int i = 0; i < coo.size; i++) {
        printf("%d ", coo.row[i]);
    }
    printf("\nColumn: ");
    for (int i = 0; i < coo.size; i++) {
        printf("%d ", coo.col[i]);
    }
    printf("\nValue: ");
    for (int i = 0; i < coo.size; i++) {
        printf("%.2f ", coo.value[i]);
    }
    printf("\n");

    freeCOO(&coo);
    for (int i = 0; i < numRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    demo2COO();
    return 0;
}
