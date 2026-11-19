#include <vector>
#include <algorithm>
class Solution {
public:
    int trap(std::vector<int>& height) {
        if (height.empty()) return 0;
        int left = 0, right = static_cast<int>(height.size()) - 1;
        int leftMax = 0, rightMax = 0, water = 0;
        while (left <= right) {
            leftMax = std::max(leftMax, height[left]);
            rightMax = std::max(rightMax, height[right]);
            if (leftMax <= rightMax) {
                water += leftMax - height[left];
                ++left;
            } else {
                water += rightMax - height[right];
                --right;
            }
        }
        return water;
    }
};
