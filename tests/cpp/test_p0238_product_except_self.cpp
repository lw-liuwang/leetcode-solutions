#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
#include "../../cpp/p0238_product_except_self.cpp"

std::vector<int> oracle(const std::vector<int>& values) {
    std::vector<int> result;
    for (std::size_t excluded = 0; excluded < values.size(); ++excluded) {
        long long product = 1;
        for (std::size_t i = 0; i < values.size(); ++i)
            if (i != excluded) product *= values[i];
        assert(product >= INT_MIN && product <= INT_MAX);
        result.push_back(static_cast<int>(product));
    }
    return result;
}
void exact(std::vector<int> values, const std::vector<int>& expected) {
    const auto before = values;
    assert(Solution().productExceptSelf(values) == expected);
    assert(values == before);
    std::reverse(values.begin(), values.end());
    auto reversedExpected = expected;
    std::reverse(reversedExpected.begin(), reversedExpected.end());
    const auto reversedBefore = values;
    assert(Solution().productExceptSelf(values) == reversedExpected);
    assert(values == reversedBefore);
}
void enumerate(std::vector<int>& values, int remaining, int& checked) {
    if (!remaining) { exact(values, oracle(values)); ++checked; return; }
    for (int value : {-2, -1, 0, 1, 2}) {
        values.push_back(value);
        enumerate(values, remaining - 1, checked);
        values.pop_back();
    }
}
int main() {
    exact({1, 2, 3, 4}, {24, 12, 8, 6});
    exact({-1, 1, 0, -3, 3}, {0, 0, 9, 0, 0});
    exact({0, 2, 0}, {0, 0, 0});
    exact({-2, 3}, {3, -2});
    int checked = 0;
    std::vector<int> values;
    for (int length = 2; length <= 7; ++length) enumerate(values, length, checked);
    assert(checked == 97650);
    exact(std::vector<int>(31, -2), std::vector<int>(31, 1073741824));
    std::vector<int> boundary(100000, 1);
    exact(boundary, boundary);
    boundary[50000] = 0;
    std::vector<int> oneZero(100000, 0);
    oneZero[50000] = 1;
    exact(boundary, oneZero);
    boundary[90000] = 0;
    exact(boundary, std::vector<int>(100000, 0));
    std::cout << checked << " arrays matched excluded-index product oracle; 97658 reversal checks; 4 fixtures and 4 integer/length boundaries passed\n";
}
