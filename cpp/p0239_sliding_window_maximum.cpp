#include <deque>
#include <vector>

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        std::deque<int> candidates;
        std::vector<int> result;
        const int n = static_cast<int>(nums.size());
        result.reserve(n - k + 1);
        for (int right = 0; right < n; ++right) {
            while (!candidates.empty() && candidates.front() <= right - k) {
                candidates.pop_front();
            }
            while (!candidates.empty() && nums[candidates.back()] <= nums[right]) {
                candidates.pop_back();
            }
            candidates.push_back(right);
            if (right >= k - 1) result.push_back(nums[candidates.front()]);
        }
        return result;
    }
};
