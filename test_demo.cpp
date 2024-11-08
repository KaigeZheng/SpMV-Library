#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "SpMV_CXX.h"
#define EPOCH 1000

void testSpMV(int size);
std::vector<std::vector<double>> generateMatrix(int size);
std::vector<double> generateVector(int size);

int main() {
    std::vector<int> sizes = {8, 16, 32, 64, 128, 256, 512, 1024};

    for (int size : sizes) {
        testSpMV(size);
    }

    return 0;
}

void testSpMV(int size) {
    std::vector<std::vector<double>> matrix = generateMatrix(size);
    std::vector<double> x = generateVector(size);

    // Test COO Trans
    auto start = std::chrono::high_resolution_clock::now();
    COO coo = convert2COO(matrix);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cooConversionTime = end - start;

    // Test CSR Trans
    start = std::chrono::high_resolution_clock::now();
    CSR csr = convert2CSR(matrix);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> csrConversionTime = end - start;

    // Test 2D SpMV
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> result2D = SpMV_2D(matrix, x);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> spmv2DTime = end - start;

    // Test COO SpMV
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> resultCOO = SpMV_COO(coo, x);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> spmvCOOTime = end - start;

    // Test CSR SpMV
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