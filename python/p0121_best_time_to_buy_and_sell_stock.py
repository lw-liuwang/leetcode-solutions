"""LeetCode 121: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/.

Track the cheapest earlier price and the best single-transaction profit.
One pass takes O(n) time and O(1) auxiliary space without slicing the input.
"""


class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        if not prices:
            return 0
        minimum = prices[0]
        best = 0
        for price in prices:
            best = max(best, price - minimum)
            minimum = min(minimum, price)
        return best
