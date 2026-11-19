#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>
#include "../../cpp/p0128_longest_consecutive_sequence.cpp"

int oracle(std::vector<int> values) {
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());
    int best = 0, run = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
        run = i > 0 && static_cast<long long>(values[i]) - values[i - 1] == 1 ? run + 1 : 1;
        best = std::max(best, run);
    }
    return best;
}
void exact(std::vector<int> values, int expected) {
    const auto before = values;
    assert(Solution().longestConsecutive(values) == expected);
    assert(values == before);
}
void enumerate(std::vector<int>& values, int remaining, int& checked) {
    if (!remaining) {
        const int expected = oracle(values);
        exact(values, expected);
        auto shifted = values;
        for (auto& value : shifted) value += 7;
        exact(shifted, expected);
        if (!values.empty()) {
            auto duplicated = values;
            duplicated.push_back(values.front());
            exact(duplicated, expected);
        }
        ++checked;
        return;
    }
    for (int value : {-2, -1, 0, 1, 2}) {
        values.push_back(value);
        enumerate(values, remaining - 1, checked);
        values.pop_back();
    }
}
int main() {
    exact({100, 4, 200, 1, 3, 2}, 4);
    exact({1, 2, 0, 1}, 3);
    exact({-3, -2, 1, 2}, 2);
    exact({INT_MIN, INT_MIN + 1, INT_MAX - 1, INT_MAX}, 2);
    exact({INT_MIN, INT_MAX}, 1);
    int checked = 0;
    std::vector<int> values;
    for (int length = 0; length <= 7; ++length) enumerate(values, length, checked);
    assert(checked == 97656);
    std::vector<int> boundary(100000);
    std::iota(boundary.begin(), boundary.end(), -50000);
    std::reverse(boundary.begin(), boundary.end());
    exact(boundary, 100000);
    exact(std::vector<int>(100000, 7), 1);
    std::cout << checked << " arrays matched sorting oracle; 97656 translation and 97655 existing-value duplication checks; 5 fixtures and 2 length boundaries passed\n";
}
