#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "../../cpp/p0150_evaluate_rpn.cpp"

void exact(std::vector<std::string> tokens, int expected) {
    const auto before = tokens;
    assert(Solution().evalRPN(tokens) == expected);
    assert(tokens == before);
}
struct Expression { std::vector<std::string> tokens; int value; };

int main() {
    // Literal expectations catch operand reversal and floor-vs-zero division.
    exact({"2", "1", "+", "3", "*"}, 9);
    exact({"4", "13", "5", "/", "+"}, 6);
    exact({"-7", "3", "/"}, -2);
    exact({"7", "-3", "/"}, -2);
    exact({"-7", "-3", "/"}, 2);
    exact({"10", "3", "-"}, 7);
    exact({"3", "10", "-"}, -7);
    exact({"-200", "200", "*"}, -40000);
    exact({"200", "200", "*", "200", "*", "200", "*", "200", "+"}, 1600000200);
    exact({"-200"}, -200);

    // Generate expression trees from subexpressions with independently known
    // values; no RPN evaluation stack is used to derive these expectations.
    std::vector<std::vector<Expression>> trees(5);
    for (int value = -2; value <= 2; ++value)
        trees[1].push_back({{std::to_string(value)}, value});
    int checked = 0;
    for (int leaves = 1; leaves <= 4; ++leaves) {
        if (leaves > 1) {
            for (int leftSize = 1; leftSize < leaves; ++leftSize)
                for (const auto& left : trees[leftSize])
                    for (const auto& right : trees[leaves - leftSize])
                        for (char operation : std::string("+-*/")) {
                            if (operation == '/' && right.value == 0) continue;
                            int expected = 0;
                            if (operation == '+') expected = left.value + right.value;
                            if (operation == '-') expected = left.value - right.value;
                            if (operation == '*') expected = left.value * right.value;
                            if (operation == '/') {
                                // Magnitude division with an explicit sign.
                                expected = std::abs(left.value) / std::abs(right.value);
                                if ((left.value < 0) != (right.value < 0)) expected = -expected;
                            }
                            auto tokens = left.tokens;
                            tokens.insert(tokens.end(), right.tokens.begin(), right.tokens.end());
                            tokens.emplace_back(1, operation);
                            trees[leaves].push_back({tokens, expected});
                        }
        }
        for (const auto& tree : trees[leaves]) {
            exact(tree.tokens, tree.value);
            auto identity = tree.tokens;
            identity.push_back("0");
            identity.push_back("+");
            exact(identity, tree.value);
            identity = tree.tokens;
            identity.push_back("1");
            identity.push_back("*");
            exact(identity, tree.value);
            ++checked;
        }
    }
    std::vector<std::string> wide(5000, "200");
    wide.insert(wide.end(), 4999, "+");
    assert(wide.size() == 9999);
    exact(wide, 1000000);
    std::vector<std::string> chain{"0"};
    for (int i = 0; i < 4999; ++i) { chain.push_back("200"); chain.push_back("-"); }
    assert(chain.size() == 9999);
    exact(chain, -999800);
    std::cout << checked << " valid generated expression trees, 10 exact fixtures and 2 length9999 expressions passed; 342210 small-expression identity checks; input unchanged\n";
}
