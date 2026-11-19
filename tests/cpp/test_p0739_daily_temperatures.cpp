#include <cassert>
#include <iostream>
#include <vector>
#include "../../cpp/p0739_daily_temperatures.cpp"

std::vector<int> oracle(const std::vector<int>& values) {
    std::vector<int> result(values.size(), 0);
    for (std::size_t i = 0; i < values.size(); ++i)
        for (std::size_t j = i + 1; j < values.size(); ++j)
            if (values[j] > values[i]) { result[i] = static_cast<int>(j - i); break; }
    return result;
}
void exact(std::vector<int> values, const std::vector<int>& expected) {
    const auto before = values;
    assert(Solution().dailyTemperatures(values) == expected);
    assert(values == before);
}
void enumerate(std::vector<int>& values, int remaining, int& checked) {
    if (!remaining) {
        const auto expected = oracle(values);
        exact(values, expected);
        bool canShift = !values.empty();
        for (int value : values) if (value == 100) canShift = false;
        if (canShift) {
            auto shifted = values;
            for (int& value : shifted) ++value;
            exact(shifted, expected);
        }
        ++checked;
        return;
    }
    for (int value : {30, 31, 32, 100}) {
        values.push_back(value);
        enumerate(values, remaining - 1, checked);
        values.pop_back();
    }
}
int main() {
    exact({73, 74, 75, 71, 69, 72, 76, 73}, {1, 1, 4, 2, 1, 1, 0, 0});
    exact({30, 40, 50, 60}, {1, 1, 1, 0});
    exact({73, 73, 74}, {2, 1, 0});
    exact({100, 30, 100}, {0, 1, 0});
    int checked = 0;
    std::vector<int> values;
    for (int length = 0; length <= 8; ++length) enumerate(values, length, checked);
    assert(checked == 87381);
    const int size = 100000;
    std::vector<int> boundary(size, 70), expected(size, 0);
    exact(boundary, expected);
    boundary.back() = 71;
    for (int i = 0; i + 1 < size; ++i) expected[i] = size - 1 - i;
    exact(boundary, expected);
    for (int i = 0; i < size; ++i) {
        boundary[i] = 100 - i % 71;
        const int nextPeak = (i / 71 + 1) * 71;
        expected[i] = i % 71 && nextPeak < size ? nextPeak - i : 0;
    }
    exact(boundary, expected);
    std::cout << checked << " arrays matched first-warmer scan oracle; 4 fixtures and 3 length100000 boundaries passed; 9840 legal temperature translations checked; input unchanged\n";
}
