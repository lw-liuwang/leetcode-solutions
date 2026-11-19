#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#include "../../cpp/p0125_valid_palindrome.cpp"

// A materialized normalization oracle catches filtering, case and cursor bugs.
bool oracle(const std::string& text) {
    std::string normalized;
    for (unsigned char c : text)
        if (std::isalnum(c)) normalized.push_back(static_cast<char>(std::tolower(c)));
    auto reversed = normalized;
    std::reverse(reversed.begin(), reversed.end());
    return normalized == reversed;
}
void exact(const std::string& text, bool expected) {
    const auto before = text;
    assert(Solution().isPalindrome(text) == expected);
    assert(text == before);
}
void punctuationCheck(const std::string& text, bool expected) {
    std::string decorated = "!";
    for (char c : text) { decorated.push_back(c); decorated.push_back('!'); }
    exact(decorated, expected);
}
void enumerate(std::string& text, int remaining, int& count) {
    if (!remaining) {
        const bool expected = oracle(text);
        exact(text, expected);
        punctuationCheck(text, expected);
        ++count;
        return;
    }
    for (char c : std::string("aAbB01 ,")) {
        text.push_back(c);
        enumerate(text, remaining - 1, count);
        text.pop_back();
    }
}
int main() {
    exact("A man, a plan, a canal: Panama", true);
    exact("race a car", false);
    exact(" ", true);
    exact("0P", false);
    exact("ab_a", true);
    exact("1a2", false);
    exact("a.", true);
    exact("aa", true);
    int count = 0;
    std::string text;
    for (int length = 0; length <= 6; ++length) enumerate(text, length, count);
    assert(count == 299593);
    int pairs = 0;
    for (char first = 32; first <= 126; ++first)
        for (char second = 32; second <= 126; ++second) {
            std::string pair{first, second};
            const bool expected = oracle(pair);
            exact(pair, expected);
            punctuationCheck(pair, expected);
            ++pairs;
        }
    assert(pairs == 9025);
    exact(std::string(200000, ','), true);
    std::string boundary(200000, 'A');
    exact(boundary, true);
    boundary.back() = 'b';
    exact(boundary, false);
    std::cout << count << " strings and 9025 printable-ASCII pairs matched normalization oracle; 8 fixtures and 3 length boundaries passed; 308618 punctuation-insertion checks\n";
}
