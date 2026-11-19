#include <vector>

class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) {
        const int size = static_cast<int>(nums.size());
        int left = 0, right = size;
        while (left < right) {
            const int middle = left + (right - left) / 2;
            if (nums[middle] < target) left = middle + 1;
            else right = middle;
        }
        const int first = left;
        if (first == size || nums[first] != target) return {-1, -1};
        right = size;
        while (left < right) {
            const int middle = left + (right - left) / 2;
            if (nums[middle] <= target) left = middle + 1;
            else right = middle;
        }
        return {first, left - 1};
    }
};
