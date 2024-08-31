//
// Created by stellaura on 31/08/24.
//
#include <catch2/catch_all.hpp>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    string reverseWords(string s) {
        // 格式化 去除多与的空格
        bool contiuous_space = false;
        int i = 0, j = 0;
        // 去除开头的空格
        while(s[j]==' ') j++;

        while (j < s.size()) {
            if (s[j] == ' ') {
                if (!contiuous_space) {
                    s[i++] = s[j];
                }
                j++;
                contiuous_space = true;
            } else {
                s[i++] = s[j++];
                contiuous_space = false;
            }
        }

        // 去除结尾的空格
        if(s[i-1] == ' ') i--;

        // 抛弃后面多与的内容
        s.resize(i);

        // 翻转两次
        reverse(s.begin(), s.end());

        auto begin = s.begin();
        auto current = s.begin();
        while (true) {
            if (current == s.end()) {
                reverse(begin, current);
                break;
            }

            if (*current == ' ') {
                reverse(begin, current);
                begin = current + 1;
            }

            current++;
        }
        return s;
    }
};

TEST_CASE("Reverse Words in a String", "[reverseWords]") {
    Solution s;
    REQUIRE(s.reverseWords("the sky is blue") == "blue is sky the");
    REQUIRE(s.reverseWords("  hello world!  ") == "world! hello");
}