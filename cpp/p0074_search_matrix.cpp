#include <vector>

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix.front().empty()) return false;
        const int rows = static_cast<int>(matrix.size());
        const int columns = static_cast<int>(matrix.front().size());
        int left = 0, right = rows * columns;
        while (left < right) {
            const int middle = left + (right - left) / 2;
            const int value = matrix[middle / columns][middle % columns];
            if (value == target) return true;
            if (value < target) left = middle + 1;
            else right = middle;
        }
        return false;
    }
};
