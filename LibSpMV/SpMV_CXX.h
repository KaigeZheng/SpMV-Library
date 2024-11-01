#include <iostream>
#include <vector>
#include <map>

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