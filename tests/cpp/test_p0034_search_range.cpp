#include "../../cpp/p0034_search_range.cpp"
#include <cassert>
#include <iostream>
#include <vector>

std::vector<int> scan(const std::vector<int>& values, int target) {
    int first = -1, last = -1;
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        if (values[i] == target) {
            if (first == -1) first = i;
            last = i;
        }
    }
    return {first, last};
}

void exact(std::vector<int> values, int target, const std::vector<int>& expected) {
    const auto before = values;
    assert(Solution().searchRange(values, target) == expected);
    assert(values == before);
}

void enumerate(std::vector<int>& values, int remaining, int minimum,
               int& arrays, int& queries) {
    if (remaining == 0) {
        ++arrays;
        for (int target = -3; target <= 3; ++target) {
            exact(values, target, scan(values, target));
            ++queries;
        }
        return;
    }
    for (int value = minimum; value <= 2; ++value) {
        values.push_back(value);
        enumerate(values, remaining - 1, value, arrays, queries);
        values.pop_back();
    }
}

int main() {
    exact({5,7,7,8,8,10}, 8, {3,4});
    exact({5,7,7,8,8,10}, 6, {-1,-1});
    exact({2,2,2}, 2, {0,2});
    exact({2,2,2}, 1, {-1,-1});
    exact({1}, 1, {0,0});
    exact({-1000000000,-1000000000,0,1000000000,1000000000}, -1000000000, {0,1});
    exact({-1000000000,-1000000000,0,1000000000,1000000000}, 1000000000, {3,4});
    exact({}, 0, {-1,-1});
    int arrays = 0, queries = 0;
    std::vector<int> values;
    for (int length = 0; length <= 8; ++length) {
        enumerate(values, length, -2, arrays, queries);
    }
    assert(arrays == 1287 && queries == 9009);
    exact(std::vector<int>(100000, 1000000000), 1000000000, {0,99999});
    exact(std::vector<int>(100000, -1000000000), 0, {-1,-1});
    std::vector<int> large(100000);
    for (int i = 0; i < 100000; ++i) large[i] = i / 10 - 5000;
    exact(large, -5000, {0,9});
    exact(large, 0, {50000,50009});
    exact(large, 4999, {99990,99999});
    std::cout << "1287 sorted arrays / 9009 linear-oracle queries; 8 fixtures and 5 maximum-length checks passed; input unchanged\n";
}
