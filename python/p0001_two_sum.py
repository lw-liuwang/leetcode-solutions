"""LeetCode 1: https://leetcode.com/problems/two-sum/.

Keep the index of each previously seen value. Checking the complement before
inserting the current value ensures the two returned indices are distinct.
Expected O(n) time and O(n) auxiliary space with a hash table.
"""


class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        seen: dict[int, int] = {}
        for index, value in enumerate(nums):
            complement = target - value
            if complement in seen:
                return [seen[complement], index]
            seen[value] = index
        raise ValueError("no two distinct indices sum to the target")
