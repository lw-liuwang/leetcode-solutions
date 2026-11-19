#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::size_t> groupIndex;
        std::vector<std::vector<std::string>> groups;
        for (const auto& word : strs) {
            std::string key = word;
            std::sort(key.begin(), key.end());
            const auto inserted = groupIndex.emplace(key, groups.size());
            if (inserted.second) groups.push_back({});
            groups[inserted.first->second].push_back(word);
        }
        return groups;
    }
};
