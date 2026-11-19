#include <string>
class Solution {
    static int normalized(unsigned char c) {
        if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) return c;
        return -1;
    }
public:
    bool isPalindrome(const std::string& s) {
        int left = 0;
        int right = static_cast<int>(s.size()) - 1;
        while (left < right) {
            const int first = normalized(static_cast<unsigned char>(s[left]));
            const int last = normalized(static_cast<unsigned char>(s[right]));
            if (first < 0) { ++left; continue; }
            if (last < 0) { --right; continue; }
            if (first != last) return false;
            ++left;
            --right;
        }
        return true;
    }
};
