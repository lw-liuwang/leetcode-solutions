import unittest

from python.p0001_two_sum import Solution


class TwoSumTests(unittest.TestCase):
    def test_distinct_duplicate_and_negative_values(self):
        cases = [
            ([2, 7, 11, 15], 9),
            ([3, 2, 4], 6),
            ([3, 3], 6),
            ([-3, 4, 3, 90], 0),
            ([0, 4, 3, 0], 0),
        ]
        for values, target in cases:
            with self.subTest(values=values, target=target):
                before = values.copy()
                left, right = Solution().twoSum(values, target)
                self.assertNotEqual(left, right)
                self.assertTrue(0 <= left < len(values) and 0 <= right < len(values))
                self.assertEqual(values[left] + values[right], target)
                self.assertEqual(values, before)

    def test_absent_pair_is_explicit(self):
        for values in [[], [3], [1, 2]]:
            with self.subTest(values=values), self.assertRaises(ValueError):
                Solution().twoSum(values, 6)


if __name__ == "__main__":
    unittest.main()
