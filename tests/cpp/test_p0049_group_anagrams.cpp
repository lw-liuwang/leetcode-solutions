#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "../../cpp/p0049_group_anagrams.cpp"

using Groups = std::vector<std::vector<std::string>>;
Groups normalized(Groups groups) {
    for (auto& group : groups) std::sort(group.begin(), group.end());
    std::sort(groups.begin(), groups.end());
    return groups;
}
std::array<int, 26> counts(const std::string& word) {
    std::array<int, 26> result{};
    for (char ch : word) ++result[ch - 'a'];
    return result;
}
Groups oracle(const std::vector<std::string>& words) {
    Groups result;
    for (const auto& word : words) {
        bool matched = false;
        for (auto& group : result) {
            if (counts(word) == counts(group.front())) {
                group.push_back(word);
                matched = true;
                break;
            }
        }
        if (!matched) result.push_back({word});
    }
    return result;
}
void exact(std::vector<std::string> words, const Groups& expected) {
    const auto before = words;
    assert(normalized(Solution().groupAnagrams(words)) == normalized(expected));
    assert(words == before);
    for (auto& word : words) std::reverse(word.begin(), word.end());
    auto reversedExpected = expected;
    for (auto& group : reversedExpected)
        for (auto& word : group) std::reverse(word.begin(), word.end());
    const auto reversedBefore = words;
    assert(normalized(Solution().groupAnagrams(words)) == normalized(reversedExpected));
    assert(words == reversedBefore);
}
void enumerate(std::vector<std::string>& words, int remaining, int& checked) {
    if (!remaining) { exact(words, oracle(words)); ++checked; return; }
    for (const std::string word : {"", "a", "b", "aa", "ab", "ba", "bb", "abc"}) {
        words.push_back(word);
        enumerate(words, remaining - 1, checked);
        words.pop_back();
    }
}
int main() {
    exact({"eat", "tea", "tan", "ate", "nat", "bat"}, {{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}});
    exact({"", "", "a"}, {{"", ""}, {"a"}});
    exact({"ab", "aab", "aba", "ba", "ab"}, {{"ab", "ba", "ab"}, {"aab", "aba"}});
    int checked = 0;
    std::vector<std::string> words;
    for (int length = 0; length <= 4; ++length) enumerate(words, length, checked);
    assert(checked == 4681);
    const std::string a(100, 'a'), b(100, 'b');
    std::vector<std::string> boundary(5000, a);
    boundary.insert(boundary.end(), 5000, b);
    exact(boundary, {std::vector<std::string>(5000, a), std::vector<std::string>(5000, b)});
    std::cout << checked << " word lists matched count-based partition oracle; word-reversal partition checks; 3 fixtures and 10000-word boundary passed\n";
}
