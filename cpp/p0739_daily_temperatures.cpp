#include <vector>
class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        std::vector<int> answer(temperatures.size(), 0);
        std::vector<int> pending;
        pending.reserve(temperatures.size());
        for (int day = 0; day < static_cast<int>(temperatures.size()); ++day) {
            while (!pending.empty() && temperatures[day] > temperatures[pending.back()]) {
                const int previous = pending.back();
                pending.pop_back();
                answer[previous] = day - previous;
            }
            pending.push_back(day);
        }
        return answer;
    }
};
