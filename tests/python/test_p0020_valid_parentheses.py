import unittest

from python.p0020_valid_parentheses import Solution


class ValidParenthesesTests(unittest.TestCase):
    def test_balanced_and_nested(self):
        for text in ["", "()", "()[]{}", "{[()]}", "([]){}"]:
            with self.subTest(text=text):
                self.assertTrue(Solution().isValid(text))

    def test_wrong_type_order_and_incomplete_input(self):
        for text in ["(]", "([)]", ")(", "(", "]", "((())", "()a"]:
            with self.subTest(text=text):
                self.assertFalse(Solution().isValid(text))


if __name__ == "__main__":
    unittest.main()
