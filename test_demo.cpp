#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
//#include "SpMV_CXX.h"
#define EPOCH 1000

struct COO {
    std::vector<int> row;
    std::vector<int> col;
    std::vector<double> value;
};

struct CSR {
    std::vector<int> rowPtr;
    std::vector<int> index;
    std::vector<double> value;
};

COO convert2COO(const std::vector<std::vector<double>>& matrix) {
    COO coo;
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    for(int i = 0; i < numRows; ++i) {
        for(int j = 0; j < numCols; ++j) {
            if(matrix[i][j] != 0) {
                coo.row.push_back(i);
                coo.col.push_back(j);
                coo.value.push_back(matrix[i][j]);
            }
        }
    }
    return coo;
}

CSR convert2CSR(const std::vector<std::vector<double>>& matrix) {
    CSR csr;
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    
    csr.rowPtr.resize(numRows + 1, 0);

    for(int i = 0; i < numRows; ++i) {
        for(int j = 0; j < numCols; ++j) {
            if(matrix[i][j] != 0) {
                csr.value.push_back(matrix[i][j]);
                csr.index.push_back(j);
                ++csr.rowPtr[i+1];
            }
        }
    }

    // 将行指针转换为累计和
    for(int i = 1; i <= numRows; ++i) {
        csr.rowPtr[i] += csr.rowPtr[i-1];
    }

    return csr;
}

std::vector<double> SpMV_2D(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    int m = A.size();
    int n = A[0].size();
    std::vector<double> result(m, 0.0);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * x[j];
        }
    }

    return result;
}

std::vector<double> SpMV_COO(const COO& coo, const std::vector<double>& x) {
    int m = x.size();
    std::vector<double> result(m, 0.0); 

    // Main algorithm of SpMV
    for (size_t i = 0; i < coo.row.size(); ++i) {
        result[coo.row[i]] += coo.value[i] * x[coo.col[i]];
    }

    return result;
}

std::vector<double> SpMV_CSR(const CSR& csr, const std::vector<double>& x) {
    int m = csr.rowPtr.size() - 1; // 行数等于 rowPtr 的大小减去 1
    std::vector<double> result(m, 0.0); 

    // Main algorithm of SpMV
    for (int i = 0; i < m; ++i) {
        for (int j = csr.rowPtr[i]; j < csr.rowPtr[i + 1]; ++j) {
            result[i] += csr.value[j] * x[csr.index[j]];
        }
    }

    return result;
}

std::vector<std::vector<double>> generateMatrix(int size) {
    std::vector<std::vector<double>> matrix(size, std::vector<double>(size, 0.0));
    double sparsity = 0.4;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = (static_cast<double>(rand()) / RAND_MAX) > sparsity ? (static_cast<double>(rand() % 10 + 1)) : 0.0;
        }
    }
    return matrix;
}

std::vector<double> generateVector(int size) {
    std::vector<double> vec(size);
    for(int i = 0; i < size; ++i) {
        vec[i] = static_cast<double>(rand() % 10 + 1);
    }
    return vec;
}

void testSpMV(int size) {
    std::vector<std::vector<double>> matrix = generateMatrix(size);
    std::vector<double> x = generateVector(size);

    // 测试 COO 转换
    auto start = std::chrono::high_resolution_clock::now();
    COO coo = convert2COO(matrix);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cooConversionTime = end - start;

    // 测试 CSR 转换
    start = std::chrono::high_resolution_clock::now();
    CSR csr = convert2CSR(matrix);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> csrConversionTime = end - start;

    // 测试 2D SpMV
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> result2D = SpMV_2D(matrix, x);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> spmv2DTime = end - start;

    // 测试 COO SpMV
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> resultCOO = SpMV_COO(coo, x);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> spmvCOOTime = end - start;

    // 测试 CSR SpMV
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> resultCSR = SpMV_CSR(csr, x);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> spmvCSRTime = end - start;

    std::cout << "Size: " << size << "x" << size << std::endl;
    std::cout << "COO Conversion Time: " << cooConversionTime.count() << " seconds" << std::endl;
    std::cout << "CSR Conversion Time: " << csrConversionTime.count() << " seconds" << std::endl;
    std::cout << "2D SpMV Time: " << spmv2DTime.count() << " seconds" << std::endl;
    std::cout << "COO SpMV Time: " << spmvCOOTime.count() << " seconds" << std::endl;
    std::cout << "CSR SpMV Time: " << spmvCSRTime.count() << " seconds" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

int main() {
    std::vector<int> sizes = {8, 16, 32, 64, 128, 256, 512, 1024};

    for (int size : sizes) {
        testSpMV(size);
    }

    return 0;
}
