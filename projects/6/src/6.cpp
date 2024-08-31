//
// Created by stellaura on 31/08/24.
//
#include <catch2/catch_all.hpp>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    string convert(string s, int numRows) { return calcSolution(s, numRows); }

    string vectorSolution(string &s, int numRows) {
        vector<vector<char>> vec_list(numRows);
        int index = 0;
        while (true) {
            // 竖着下去
            for (int i = 0; i < numRows; i++) {
                vec_list[i].push_back(s[index++]);
                if (index >= s.size()) {
                    goto end_loop;
                }
            }

            // 斜着上来
            // 只有中间的部分
            for (int i = numRows - 2; i > 0; i--) {
                vec_list[i].push_back(s[index++]);
                if (index >= s.size()) {
                    goto end_loop;
                }
            }
        }
    end_loop:

        string ret;
        ret.reserve(s.size());

        for (int i = 0; i < numRows; i++) {
            for (auto c : vec_list[i]) {
                ret.push_back(c);
            }
        }
        return ret;
    }

    string calcSolution(string &s, int numRows) {
        if (numRows == 1) {
            return s;
        }

        // 下面要求 numRows >= 1 不然会死循环
        string ret;
        ret.reserve(s.size());

        int index = 0;
        while (index < s.size()) {
            ret.push_back(s[index]);
            index += 2 * numRows - 2;
        }

        for (int i = 1; i <= numRows - 2; i++) {
            index = i;
            while (index < s.size()) {
                ret.push_back(s[index]);
                // index - i 回到开始位置
                // + numRows * 2 - 2 去到下一个周期的开始位置
                // - i 然后倒回来
                // 这里可能是超出范围的
                if (index + numRows * 2 - 2 - 2 * i >= s.size()) {
                    break;
                }
                ret.push_back(s[index + numRows * 2 - 2 - 2 * i]);
                index += 2 * numRows - 2;
            }
        }

        index = numRows - 1;
        while (index < s.size()) {
            ret.push_back(s[index]);
            index += 2 * numRows - 2;
        }
        return ret;
    }
};

TEST_CASE("Test Solution") {
    Solution solution;
    REQUIRE(solution.convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
    REQUIRE(solution.convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
    REQUIRE(solution.convert("PAYPALISHIRING", 1) == "PAYPALISHIRING");
    REQUIRE(solution.convert("A", 4) == "A");
    REQUIRE(solution.convert("A", 1) == "A");
}