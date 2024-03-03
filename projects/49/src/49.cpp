//
// Created by stellaura on 02/03/24.
//

#include "fmt/format.h"
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Solution {
  public:
    // 将字符串转换为一个ASCII码桶，计数每个字符的出现次数
    static std::array<short, 26> convert(const std::string &str) {
        std::array<short, 26> count{};
        for (char c : str) {
            count[static_cast<std::size_t>(c - 'a')]++;
        }
        return count;
    }

    // 主函数
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> strs) {
        // 使用std::map来分组具有相同字符计数的字符串
        std::map<std::array<short, 26>, std::vector<std::string>> tree_map;

        for (auto &str : strs) {
            auto bucket = convert(str);
            tree_map[bucket].push_back(std::move(str));
        }

        // 将map转换为vector<vector<string>>，使用std::move优化内存使用
        std::vector<std::vector<std::string>> result;
        for (auto &pair : tree_map) {
            result.push_back(std::move(pair.second));
        }

        return result;
    }
};

int main() {
    Solution solution{};
    auto result = solution.groupAnagrams(std::vector<std::string>{"eat", "tea", "tan", "ate", "nat", "bat"});

    for (const auto &inner_vec : result) {
        for (const auto &str : inner_vec) {
            std::cout << str << " ";
        }
        std::cout << std::endl; // 在每个内部向量之后换行
    }
    return 0;
}
