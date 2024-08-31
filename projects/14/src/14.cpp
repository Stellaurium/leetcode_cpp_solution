//
// Created by stellaura on 31/08/24.
//

#include <catch2/catch_all.hpp>
#include <string>
#include <vector>

using namespace std;

// 这也能拿出来当题？
// 而且这么多奇奇怪怪的算法 递归的 二分的
// 越花里胡哨越慢
class Solution {
  public:
    string longestCommonPrefix(vector<string> &strs) {
        int count = 0;
        char c;
        bool is_finished = false;
        while (true) {
            if (strs[0].size() > count) {
                c = strs[0][count];
            } else {
                goto finish;
            }
            for (int i = 1; i < strs.size(); i++) {
                if (strs[i].size() <= count || strs[i][count] != c) {
                    goto finish;
                }
            }
            count++;
        }

        finish:

        return strs[0].substr(0, count);
    }
};

TEST_CASE("Test the solution for longest common prefix", "[longestCommonPrefix]") {
    Solution solution;
    vector<string> strs;
    string expected;
    string result;

        strs = {"flower", "flow", "flight"};
        expected = "fl";
        result = solution.longestCommonPrefix(strs);
        REQUIRE(result == expected);

        strs = {"dog", "racecar", "car"};
        expected = "";
        result = solution.longestCommonPrefix(strs);
        REQUIRE(result == expected);

    strs = {"dog"};
    expected = "dog";
    result = solution.longestCommonPrefix(strs);
    REQUIRE(result == expected);
}