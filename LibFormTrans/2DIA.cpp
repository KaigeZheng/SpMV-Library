#include <iostream>
#include <vector>
#include <map>

struct DIA {
    std::vector<int> offset;
    std::vector<int> index;
    std::vector<double> value; // 记录每条对角线上的非零元素数量
};

DIA convert2DIA(const std::vector<std::vector<double>>& matrix) {
    DIA dia;
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    std::map<int, std::vector<double>> diaMap;

    for(int i = 0; i < numRows; ++i) {
        for(int j = 0; j < numCols; ++j) {
            if(matrix[i][j] != 0) {
                int diaIndex = j - i; // 计算offset
                diaMap[diaIndex].push_back(matrix[i][j]);
                // 若为非零元,则计算应该放在DIA矩阵的偏移量(offset),并插入元素
            }
        }
    }

    for(const auto& entry : diaMap) {
        dia.offset.push_back(entry.first);
        dia.index.push_back(entry.second.size());
        dia.value.insert(dia.value.end(), entry.second.begin(), entry.second.end());
    }

    return dia;
}

void demo2DIA() {
    std::vector<std::vector<double>> matrix = {
        {1, 2, 3},
        {0, 0, 0},
        {1, 0, 3}
    };

    DIA dia = convert2DIA(matrix);

    std::cout << "Offsets: ";
    for (int offset : dia.offset) {
        std::cout << offset << " ";
    }
    std::cout << "\nValues: ";
    for (double val : dia.value) {
        std::cout << val << " ";
    }
    std::cout << "\nIndex: ";
    for (int idx : dia.index) {
        std::cout << idx << " ";
    }
    std::cout << std::endl;
}

int main() {
    demo2DIA();
    return 0;
}