#include <iostream>
#include <vector>

struct CSR {
    std::vector<int> rowPtr;
    std::vector<int> index;
    std::vector<double> value;
};

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

void demo2CSR() {
    std::vector<std::vector<double>> matrix = {
        {1, 2, 3},
        {0, 1, 0},
        {0, 0, 3}
    };

    CSR csr = convert2CSR(matrix);

    std::cout << "Row Pointer: ";
    for (int ptr : csr.rowPtr) {
        std::cout << ptr << " ";
    }
    std::cout << "\nColumn Index: ";
    for (int col : csr.index) {
        std::cout << col << " ";
    }
    std::cout << "\nValues: ";
    for (double val : csr.value) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    demo2CSR();
    return 0;
}