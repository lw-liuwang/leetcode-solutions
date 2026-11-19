"""LeetCode 704: https://leetcode.com/problems/binary-search/.

Search a sorted array of distinct integers using a half-open [left, right)
interval. O(log n) time and O(1) auxiliary space.
"""


class Solution:
    def search(self, nums: list[int], target: int) -> int:
        left, right = 0, len(nums)
        while left < right:
            middle = left + (right - left) // 2
            if nums[middle] < target:
                left = middle + 1
            elif nums[middle] > target:
                right = middle
            else:
                return middle
        return -1
