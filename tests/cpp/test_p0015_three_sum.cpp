#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
#include "../../cpp/p0015_three_sum.cpp"

using Triples = std::vector<std::vector<int>>;
Triples normalized(Triples groups) {
    for (auto& group : groups) {
        assert(group.size() == 3);
        std::sort(group.begin(), group.end());
    }
    std::sort(groups.begin(), groups.end());
    return groups;
}
Triples oracle(const std::vector<int>& values) {
    std::set<std::array<int, 3>> unique;
    for (std::size_t i = 0; i < values.size(); ++i)
        for (std::size_t j = i + 1; j < values.size(); ++j)
            for (std::size_t k = j + 1; k < values.size(); ++k)
                if (static_cast<long long>(values[i]) + values[j] + values[k] == 0) {
                    std::array<int, 3> triple{values[i], values[j], values[k]};
                    std::sort(triple.begin(), triple.end());
                    unique.insert(triple);
                }
    Triples result;
    for (const auto& triple : unique) result.push_back({triple.begin(), triple.end()});
    return result;
}
void exact(std::vector<int> values, const Triples& expected) {
    const auto before = values;
    assert(normalized(Solution().threeSum(values)) == normalized(expected));
    assert(values == before);
}
void enumerate(std::vector<int>& values, int remaining, int& checked) {
    if (!remaining) {
        const auto expected = oracle(values);
        exact(values, expected);
        auto negated = values;
        for (int& value : negated) value = -value;
        auto negatedExpected = expected;
        for (auto& triple : negatedExpected)
            for (int& value : triple) value = -value;
        exact(negated, negatedExpected);
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
    exact({-2, 0, 1, 1, 2}, {{-2, 0, 2}, {-2, 1, 1}});
    exact({0, 0, 0, 0}, {{0, 0, 0}});
    exact({2, 3, 4}, {});
    exact({INT_MIN, 1, INT_MAX, 0}, {{INT_MIN, 1, INT_MAX}});
    exact({INT_MIN, INT_MIN, 0}, {});
    exact({INT_MAX, INT_MAX, 2}, {});
    exact({}, {});
    exact({0}, {});
    exact({0, 0}, {});
    std::vector<int> values;
    int checked = 0;
    for (int length = 3; length <= 7; ++length) enumerate(values, length, checked);
    assert(checked == 97625);
    exact(std::vector<int>(3000, 0), {{0, 0, 0}});
    std::vector<int> positive(3000);
    std::iota(positive.begin(), positive.end(), 1);
    std::reverse(positive.begin(), positive.end());
    exact(positive, {});
    std::cout << checked << " arrays matched index-triple oracle; 6 fixtures, 3 short extensions and 2 length boundaries passed; small-value negation checked\n";
}
