#include <iostream>
#include <vector>

struct COO {
    std::vector<int> row;
    std::vector<int> col;
    std::vector<double> value;
};

std::vector<double> SpMV_COO(const COO& coo, const std::vector<double>& x) {
    int m = x.size();
    std::vector<double> result(m, 0.0); 

    for (size_t i = 0; i < coo.row.size(); ++i) {
        result[coo.row[i]] += coo.value[i] * x[coo.col[i]];
    }

    return result;
}

void demo_COO() {
    COO coo;
    coo.row = {0, 0, 1, 1, 2, 2, 3};
    coo.col = {0, 1, 1, 2, 0, 2, 3};
    coo.value = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}; 

    std::vector<double> x = {1, 2, 3, 4};

    std::vector<double> result = SpMV_COO(coo, x);

    for (double val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    demo_COO();
    return 0;
}
