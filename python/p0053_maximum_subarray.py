"""LeetCode 53: https://leetcode.com/problems/maximum-subarray/.

Track the best nonempty subarray ending at the current element, then the best
over all endings. O(n) time and O(1) auxiliary space, without copying a slice.
"""


class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        if not nums:
            raise ValueError("a nonempty array is required")
        ending_here = best = nums[0]
        for index in range(1, len(nums)):
            value = nums[index]
            ending_here = max(value, ending_here + value)
            best = max(best, ending_here)
        return best
