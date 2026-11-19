#include <string>
#include <vector>
class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens) {
        std::vector<int> values;
        values.reserve(tokens.size());
        for (const auto& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                const int right = values.back();
                values.pop_back();
                const int left = values.back();
                values.pop_back();
                if (token == "+") values.push_back(left + right);
                else if (token == "-") values.push_back(left - right);
                else if (token == "*") values.push_back(left * right);
                else values.push_back(left / right);
            } else {
                values.push_back(std::stoi(token));
            }
        }
        return values.back();
    }
};
