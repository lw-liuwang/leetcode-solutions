#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        const std::unordered_set<int> values(nums.begin(), nums.end());
        int best = 0;
        for (int value : values) {
            if (value != INT_MIN && values.count(value - 1)) continue;
            int current = value, length = 1;
            while (current != INT_MAX && values.count(current + 1)) {
                ++current;
                ++length;
            }
            best = std::max(best, length);
        }
        return best;
    }
};
