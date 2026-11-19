#include "../../cpp/p0033_rotated_search.cpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int linear(const std::vector<int>& values, int target) {
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        if (values[i] == target) return i;
    }
    return -1;
}

void exact(std::vector<int> values, int target, int expected) {
    const auto before = values;
    assert(Solution().search(values, target) == expected);
    assert(values == before);
}

int main() {
    exact({4,5,6,7,0,1,2}, 0, 4);
    exact({4,5,6,7,0,1,2}, 3, -1);
    exact({1}, 1, 0);
    exact({1}, 0, -1);
    exact({3,1}, 1, 1);
    exact({1,3}, 3, 1);
    exact({-10000,0,10000}, 10000, 2);
    exact({10000,-10000,0}, -10000, 1);
    int rotations = 0, queries = 0;
    for (unsigned mask = 1; mask < 128; ++mask) {
        std::vector<int> sorted;
        for (int bit = 0; bit < 7; ++bit) {
            if (mask & (1U << bit)) sorted.push_back(bit - 3);
        }
        for (int offset = 0; offset < static_cast<int>(sorted.size()); ++offset) {
            auto rotated = sorted;
            std::rotate(rotated.begin(), rotated.begin() + offset, rotated.end());
            ++rotations;
            for (int target = -4; target <= 4; ++target) {
                exact(rotated, target, linear(rotated, target));
                ++queries;
            }
        }
    }
    assert(rotations == 448 && queries == 4032);
    for (int target = -4; target <= 4; ++target) exact({}, target, -1);
    std::vector<int> large(5000);
    for (int i = 0; i < 5000; ++i) large[i] = i - 2500;
    std::rotate(large.begin(), large.begin() + 1234, large.end());
    for (int target = -2501; target <= 2500; ++target) {
        exact(large, target, linear(large, target));
    }
    std::cout << "448 rotations / 4032 linear-oracle queries; 8 fixtures, 9 empty extensions and 5002 maximum-length queries passed; input unchanged\n";
}
