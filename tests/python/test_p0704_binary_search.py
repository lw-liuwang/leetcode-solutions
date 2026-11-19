from itertools import combinations
import unittest

from python.p0704_binary_search import Solution


class BinarySearchTests(unittest.TestCase):
    def test_found_absent_and_interval_boundaries(self):
        cases = [
            ([-1, 0, 3, 5, 9, 12], 9, 4),
            ([-1, 0, 3, 5, 9, 12], 2, -1),
            ([5], 5, 0),
            ([5], 4, -1),
            ([1, 3], 1, 0),
            ([1, 3], 3, 1),
            ([], 0, -1),
        ]
        for values, target, expected in cases:
            with self.subTest(values=values, target=target):
                before = values.copy()
                self.assertEqual(Solution().search(values, target), expected)
                self.assertEqual(values, before)

    def test_all_small_sorted_subsets_against_linear_lookup(self):
        for length in range(8):
            for subset in combinations(range(-3, 4), length):
                values = list(subset)
                for target in range(-4, 5):
                    expected = values.index(target) if target in values else -1
                    self.assertEqual(Solution().search(values, target), expected, (values, target))


if __name__ == "__main__":
    unittest.main()
