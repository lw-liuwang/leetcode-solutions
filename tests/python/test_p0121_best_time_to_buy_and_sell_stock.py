from itertools import product
import unittest

from python.p0121_best_time_to_buy_and_sell_stock import Solution


class StockProfitTests(unittest.TestCase):
    def test_examples_and_order_constraint(self):
        cases = [
            ([7, 1, 5, 3, 6, 4], 5),
            ([7, 6, 4, 3, 1], 0),
            ([2, 4, 1], 2),
            ([1, 1, 1], 0),
            ([8], 0),
            ([], 0),
        ]
        for prices, expected in cases:
            with self.subTest(prices=prices):
                before = prices.copy()
                self.assertEqual(Solution().maxProfit(prices), expected)
                self.assertEqual(prices, before)

    def test_small_arrays_against_all_buy_sell_pairs(self):
        for length in range(6):
            for prices in product(range(4), repeat=length):
                gains = [
                    prices[sell] - prices[buy]
                    for buy in range(length)
                    for sell in range(buy + 1, length)
                ]
                expected = max([0] + gains)
                self.assertEqual(Solution().maxProfit(list(prices)), expected, prices)


if __name__ == "__main__":
    unittest.main()
