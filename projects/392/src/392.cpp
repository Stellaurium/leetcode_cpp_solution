//
// Created by stellaura on 03/09/24.
//
#include <catch2/catch_all.hpp>
#include <string>

using namespace std;

class Solution {
  public:
    bool isSubsequence(string s, string t) { return dynamic_programming(s, t); }

    // O(m+n) 对于只有一次的匹配是合理的
    bool double_pointer(const string &s, const string &t) {
        int target_index = 0;
        int source_index = 0;
        while (target_index < t.size() && source_index < s.size()) {
            if (s[source_index] == t[target_index]) {
                source_index++;
            }
            target_index++;
        }

        if (source_index == s.size()) {
            return true;
        } else {
            return false;
        }
    }

    // 与处理target 花费O(n)
    // 然后使用O(m)的时间进行匹配
    // 动态规划
    // 创建一个数组 描述 在target字符串 第i位 之后
    // 任意字符集中的元素出现的下一个位置
    // 如果不存在 则设置为 t.size()
    // 题目中说明了两个字符串的都只有小写字母
    bool dynamic_programming(const string &s, const string &t) {
        auto dp = vector<vector<int>>(t.size() + 1, vector<int>(26, t.size()));
        for (int i = t.size() - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                if (t[i] == 'a' + j) {
                    dp[i][j] = i;
                } else {
                    dp[i][j] = dp[i + 1][j];
                }
            }
        }

        int index = 0;
        for (auto c : s) {
            index = dp[index][c - 'a'];
            if (index == t.size()) {
                return false;
            }
            index++;
        }
        return true;
    }
};

TEST_CASE("Test the solution for subsequence", "[isSubsequence]") {
    Solution solution;
    REQUIRE(solution.isSubsequence("abc", "ahbgdc") == true);
    REQUIRE(solution.isSubsequence("axc", "ahbgdc") == false);
    REQUIRE(solution.isSubsequence("aaaaaa", "bbaaaa") == false);
}