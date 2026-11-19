#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
#include "../../cpp/p0042_trapping_rain_water.cpp"

int oracle(const std::vector<int>& height) {
    int water = 0;
    for (std::size_t i = 0; i < height.size(); ++i) {
        int left = height[i], right = height[i];
        for (std::size_t j = 0; j < i; ++j) left = std::max(left, height[j]);
        for (std::size_t j = i + 1; j < height.size(); ++j) right = std::max(right, height[j]);
        water += std::min(left, right) - height[i];
    }
    return water;
}
void exact(std::vector<int> height, int expected) {
    const auto before = height;
    assert(Solution().trap(height) == expected);
    assert(height == before);
}
void enumerate(std::vector<int>& height, int remaining, int& checked) {
    if (!remaining) {
        const int expected = oracle(height);
        exact(height, expected);
        auto shifted = height;
        for (int& value : shifted) value += 5;
        exact(shifted, expected);
        ++checked;
        return;
    }
    for (int value = 0; value <= 3; ++value) {
        height.push_back(value);
        enumerate(height, remaining - 1, checked);
        height.pop_back();
    }
}
int main() {
    exact({5, 1, 2, 1, 4}, 8);
    exact({3, 0, 3}, 3);
    exact({0, 1, 2, 3}, 0);
    exact({3, 2, 1, 0}, 0);
    exact({}, 0);
    std::vector<int> height;
    int checked = 0;
    for (int length = 1; length <= 7; ++length) enumerate(height, length, checked);
    assert(checked == 21844);
    std::vector<int> basin(20000, 0);
    basin.front() = basin.back() = 100000;
    exact(basin, 1999800000);
    exact(std::vector<int>(20000, 100000), 0);
    std::vector<int> slope(20000);
    std::iota(slope.begin(), slope.end(), 0);
    exact(slope, 0);
    std::cout << checked << " arrays matched per-position maxima oracle; 4 fixtures, empty extension and 3 length boundaries passed; legal height translations checked\n";
}
