#include <vector>
#include <algorithm>
class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<int> sorted = nums;
        std::sort(sorted.begin(), sorted.end());
        std::vector<std::vector<int>> result;
        for (std::size_t first = 0; first + 2 < sorted.size(); ++first) {
            if (first && sorted[first] == sorted[first - 1]) continue;
            std::size_t left = first + 1, right = sorted.size() - 1;
            while (left < right) {
                const long long sum = static_cast<long long>(sorted[first]) + sorted[left] + sorted[right];
                if (sum < 0) ++left;
                else if (sum > 0) --right;
                else {
                    result.push_back({sorted[first], sorted[left], sorted[right]});
                    const int low = sorted[left], high = sorted[right];
                    while (left < right && sorted[left] == low) ++left;
                    while (left < right && sorted[right] == high) --right;
                }
            }
        }
        return result;
    }
};
