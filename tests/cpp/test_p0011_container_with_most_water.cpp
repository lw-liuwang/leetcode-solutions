#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "../../cpp/p0011_container_with_most_water.cpp"

int oracle(const std::vector<int>& height) {
    int best = 0;
    for (std::size_t i = 0; i < height.size(); ++i)
        for (std::size_t j = i + 1; j < height.size(); ++j)
            best = std::max(best, static_cast<int>(j - i) * std::min(height[i], height[j]));
    return best;
}
void exact(std::vector<int> height, int expected) {
    const auto before = height;
    assert(Solution().maxArea(height) == expected);
    assert(height == before);
    std::reverse(height.begin(), height.end());
    const auto reversedBefore = height;
    assert(Solution().maxArea(height) == expected);
    assert(height == reversedBefore);
}
void enumerate(std::vector<int>& height, int remaining, int& checked) {
    if (!remaining) { exact(height, oracle(height)); ++checked; return; }
    for (int value = 0; value <= 3; ++value) {
        height.push_back(value);
        enumerate(height, remaining - 1, checked);
        height.pop_back();
    }
}
int main() {
    exact({5, 1, 4, 2, 6}, 20);
    exact({1, 8, 2, 7, 1}, 14);
    exact({4, 4}, 4);
    exact({0, 7, 0}, 0);
    exact({6, 1, 6, 1, 6}, 24);
    exact({}, 0);
    exact({9}, 0);
    std::vector<int> height;
    int checked = 0;
    for (int length = 2; length <= 7; ++length) enumerate(height, length, checked);
    assert(checked == 21840);
    exact(std::vector<int>(100000, 10000), 999990000);
    std::cout << checked << " arrays matched all-pairs oracle; 5 fixtures, 2 short extensions and maximum-area boundary passed; reversal invariance checked\n";
}
