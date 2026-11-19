"""LeetCode 3: https://leetcode.com/problems/longest-substring-without-repeating-characters/.

Keep a window with distinct characters and the latest index of each character.
The left boundary only moves forward. Expected O(n) time, O(min(n, alphabet)) space.
"""


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        latest: dict[str, int] = {}
        left = 0
        best = 0
        for right, character in enumerate(s):
            if character in latest:
                left = max(left, latest[character] + 1)
            latest[character] = right
            best = max(best, right - left + 1)
        return best
