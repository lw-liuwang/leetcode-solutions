"""LeetCode 20: https://leetcode.com/problems/valid-parentheses/.

The stack holds unmatched opening brackets in their encounter order. A closing
bracket must match the most recent opening bracket. O(n) time, O(n) space.
"""


class Solution:
    def isValid(self, s: str) -> bool:
        expected_opening = {")": "(", "]": "[", "}": "{"}
        stack: list[str] = []
        for character in s:
            if character in "([{":
                stack.append(character)
            else:
                opening = expected_opening.get(character)
                if opening is None or not stack or stack.pop() != opening:
                    return False
        return not stack
