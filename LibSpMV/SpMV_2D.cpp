#include <iostream>
#include <vector>

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

void demo_2D() {
    std::vector<std::vector<double>> A = {
        {1, 0, 1},
        {0, 1, 0},
        {0, 0, 1}
    };
    std::vector<double> x = {1, 2, 3};
    std::vector<double> result = SpMV_2D(A, x);
    for (double val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    demo_2D();
    return 0;
}
