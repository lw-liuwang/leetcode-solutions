#include "../../cpp/p0074_search_matrix.cpp"
#include <cassert>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

bool scan(const Matrix& matrix, int target) {
    for (const auto& row : matrix) {
        for (int value : row) if (value == target) return true;
    }
    return false;
}

void exact(Matrix matrix, int target, bool expected) {
    const auto before = matrix;
    assert(Solution().searchMatrix(matrix, target) == expected);
    assert(matrix == before);
}

void enumerate(std::vector<int>& values, int rows, int columns, int minimum,
               int& matrices, int& queries) {
    if (static_cast<int>(values.size()) == rows * columns) {
        for (int row = 1; row < rows; ++row) {
            if (values[row * columns - 1] >= values[row * columns]) return;
        }
        Matrix matrix(rows, std::vector<int>(columns));
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                matrix[row][column] = values[row * columns + column];
            }
        }
        ++matrices;
        for (int target = -3; target <= 3; ++target) {
            exact(matrix, target, scan(matrix, target));
            ++queries;
        }
        return;
    }
    for (int value = minimum; value <= 2; ++value) {
        values.push_back(value);
        enumerate(values, rows, columns, value, matrices, queries);
        values.pop_back();
    }
}

int main() {
    exact({{1,3,5},{7,9,11}}, 3, true);
    exact({{1,3,5},{7,9,11}}, 6, false);
    exact({{-10000}}, -10000, true);
    exact({{-10000}}, 10000, false);
    exact({{1,1,1},{2,2,3}}, 2, true);
    exact({{1},{3},{5}}, 3, true);
    exact({{-10000,0,10000}}, 10000, true);
    exact({{1,1},{3,3}}, 2, false);
    int matrices = 0, queries = 0;
    std::vector<int> values;
    for (int rows = 1; rows <= 3; ++rows) {
        for (int columns = 1; columns <= 3; ++columns) {
            enumerate(values, rows, columns, -2, matrices, queries);
        }
    }
    assert(matrices == 277 && queries == 1939);
    exact({}, 0, false);
    exact({{}}, 0, false);
    Matrix large(100, std::vector<int>(100));
    for (int row = 0; row < 100; ++row) {
        for (int column = 0; column < 100; ++column) {
            large[row][column] = row * 100 + column - 5000;
        }
    }
    for (int target : {-5001,-5000,-4901,-4900,0,4999,5000}) {
        exact(large, target, scan(large, target));
    }
    for (int row = 0; row < 100; ++row) {
        for (int column = 0; column < 100; ++column) large[row][column] = row - 50;
    }
    for (int target = -51; target <= 50; ++target) {
        exact(large, target, scan(large, target));
    }
    std::cout << "277 legal matrices / 1939 scan-oracle queries; 8 fixtures, 2 empty extensions and 109 maximum-shape queries passed; input unchanged\n";
}
