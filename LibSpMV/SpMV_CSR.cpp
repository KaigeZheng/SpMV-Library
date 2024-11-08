#include <iostream>
#include <vector>

struct CSR {
    std::vector<int> rowPtr;
    std::vector<int> index;
    std::vector<double> value;
};

std::vector<double> SpMV_CSR(const CSR& csr, const std::vector<double>& x) {
    int m = csr.rowPtr.size() - 1; // The number of rows is euqal to the size of rowPtr minus 1
    std::vector<double> result(m, 0.0); 

    for (int i = 0; i < m; ++i) {
        for (int j = csr.rowPtr[i]; j < csr.rowPtr[i + 1]; ++j) {
            result[i] += csr.value[j] * x[csr.index[j]];
        }
    }

    return result;
}

void demo_CSR() {
    CSR csr;
    csr.rowPtr = {0, 2, 4, 7};
    csr.index = {0, 1, 1, 2, 0, 2, 3};
    csr.value = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}; 

    std::vector<double> x = {1, 2, 3, 4};

    std::vector<double> result = SPMV_CSR(csr, x);

    for (double val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    demo_CSR();
    return 0;
}
