from itertools import product
import unittest

from python.p0003_longest_substring_without_repeating_characters import Solution


class LongestSubstringTests(unittest.TestCase):
    def test_examples_and_left_boundary_never_moves_back(self):
        cases = [
            ("", 0),
            ("abcabcbb", 3),
            ("bbbbb", 1),
            ("pwwkew", 3),
            ("abba", 2),
            ("tmmzuxt", 5),
            ("é🙂é", 2),
        ]
        for text, expected in cases:
            with self.subTest(text=text):
                self.assertEqual(Solution().lengthOfLongestSubstring(text), expected)

    def test_small_strings_against_all_substrings(self):
        for length in range(8):
            for characters in product("abc", repeat=length):
                text = "".join(characters)
                best = 0
                for start in range(length):
                    for end in range(start + 1, length + 1):
                        candidate = text[start:end]
                        if len(set(candidate)) == len(candidate):
                            best = max(best, len(candidate))
                self.assertEqual(Solution().lengthOfLongestSubstring(text), best, text)


if __name__ == "__main__":
    unittest.main()
