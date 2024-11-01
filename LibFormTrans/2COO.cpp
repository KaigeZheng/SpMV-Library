#include <iostream>
#include <vector>

struct COO {
    std::vector<int> row;
    std::vector<int> col;
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

void demo2COO() {
    std::vector<std::vector<double>> matrix = {
        {1, 2, 3},
        {0, 1, 0},
        {0, 0, 3}
    };

    COO coo = convert2COO(matrix);
    std::cout << "Row: ";
    for (int r : coo.row) {
        std::cout << r << " ";
    }
    std::cout << "\nColumn: ";
    for (int c : coo.col) {
        std::cout << c << " ";
    }
    std::cout << "\nValue: ";
    for (double v : coo.value) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main() {
    demo2COO();
    return 0;
}