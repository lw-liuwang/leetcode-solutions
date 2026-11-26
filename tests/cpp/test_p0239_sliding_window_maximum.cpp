#include "../../cpp/p0239_sliding_window_maximum.cpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

void exact(std::vector<int> input, int k, const std::vector<int>& expected) {
    const auto before = input;
    const auto actual = Solution().maxSlidingWindow(input, k);
    assert(actual == expected);
    assert(actual.size() == input.size() - k + 1);
    assert(input == before);
}

std::vector<int> scanOracle(const std::vector<int>& input, int k) {
    std::vector<int> result;
    for (int left = 0; left + k <= static_cast<int>(input.size()); ++left) {
        result.push_back(*std::max_element(input.begin() + left, input.begin() + left + k));
    }
    return result;
}

void checkWindowProperties(const std::vector<int>& input, int k,
                           const std::vector<int>& expected) {
    auto reversedInput = input;
    auto reversedExpected = expected;
    std::reverse(reversedInput.begin(), reversedInput.end());
    std::reverse(reversedExpected.begin(), reversedExpected.end());
    exact(reversedInput, k, reversedExpected);

    const std::pair<int, int> transforms[] = {{1, -13}, {1, 17}, {2, 0}, {2500, 0}};
    for (const auto& [scale, offset] : transforms) {
        auto transformedInput = input;
        auto transformedExpected = expected;
        for (int& value : transformedInput) {
            value = scale * value + offset;
            assert(-10000 <= value && value <= 10000);
        }
        for (int& value : transformedExpected) value = scale * value + offset;
        exact(transformedInput, k, transformedExpected);
    }
}

void enumerate(std::vector<int>& input, int& arrays, int& queries) {
    if (!input.empty()) {
        ++arrays;
        for (int k = 1; k <= static_cast<int>(input.size()); ++k) {
            const auto expected = scanOracle(input, k);
            exact(input, k, expected);
            checkWindowProperties(input, k, expected);
            ++queries;
        }
    }
    if (input.size() == 8) return;
    for (int value : {-2, 0, 3}) {
        input.push_back(value);
        enumerate(input, arrays, queries);
        input.pop_back();
    }
}

void checkLiteralWindows() {
    exact({3}, 1, {3});
    exact({3, 1, 2}, 3, {3});
    exact({9, 1, 1}, 2, {9, 1});
    exact({4, 4, 1}, 2, {4, 4});
    exact({9, 4, 4, 1, 3, 0}, 3, {9, 4, 4, 3});
    exact({-7, -2, -4, -3}, 2, {-2, -2, -3});
    exact({3, 1, 4, 2, 5}, 3, {4, 4, 5});
    exact({5, 4, 3, 2, 1}, 3, {5, 4, 3});
    exact({1, 2, 3, 4, 5}, 3, {3, 4, 5});
    exact({-10000, 10000, -10000}, 2, {10000, 10000});
    exact({4, 1, 4, 0, 4}, 1, {4, 1, 4, 0, 4});
}

void checkLargeWindows() {
    std::vector<int> periodic(100000);
    for (int i = 0; i < 100000; ++i) periodic[i] = i % 20001 - 10000;
    exact(periodic, 20001, std::vector<int>(80000, 10000));
    exact(periodic, 1, periodic);
    exact(periodic, 100000, {10000});
    exact(std::vector<int>(100000, -10000), 50000, std::vector<int>(50001, -10000));
    std::vector<int> increasing(20001), expected;
    for (int i = 0; i <= 20000; ++i) increasing[i] = i - 10000;
    for (int left = 0; left <= 10001; ++left) expected.push_back(left - 1);
    exact(increasing, 10000, expected);
    std::reverse(increasing.begin(), increasing.end());
    expected.clear();
    for (int left = 0; left <= 10001; ++left) expected.push_back(10000 - left);
    exact(increasing, 10000, expected);
}

int main() {
    checkLiteralWindows();
    int arrays = 0, queries = 0;
    std::vector<int> input;
    enumerate(input, arrays, queries);
    assert(arrays == 9840 && queries == 73812);
    checkLargeWindows();
    std::cout << "9840 arrays and 73812 window queries matched scan oracle; 11 literal and 6 large cases passed; output lengths and input preservation checked; 73812 reversals, 147624 translations and 147624 positive scalings passed\n";
}
