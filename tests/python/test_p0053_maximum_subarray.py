from itertools import product
import unittest

from python.p0053_maximum_subarray import Solution


class MaximumSubarrayTests(unittest.TestCase):
    def test_nonempty_subarrays_and_all_negative_values(self):
        cases = [
            ([-2, 1, -3, 4, -1, 2, 1, -5, 4], 6),
            ([1], 1),
            ([-3, -1, -2], -1),
            ([5, 4, -1, 7, 8], 23),
            ([0, 0], 0),
        ]
        for values, expected in cases:
            with self.subTest(values=values):
                before = values.copy()
                self.assertEqual(Solution().maxSubArray(values), expected)
                self.assertEqual(values, before)

    def test_small_arrays_against_every_nonempty_slice(self):
        for length in range(1, 7):
            for values in product(range(-2, 3), repeat=length):
                expected = max(
                    sum(values[start:end])
                    for start in range(length)
                    for end in range(start + 1, length + 1)
                )
                self.assertEqual(Solution().maxSubArray(list(values)), expected, values)

    def test_empty_input_is_outside_the_problem_contract(self):
        with self.assertRaises(ValueError):
            Solution().maxSubArray([])


if __name__ == "__main__":
    unittest.main()
