//
// Created by stellaura on 19/10/24.
//
#include <catch2/catch_all.hpp>
#include <string>
#include <vector>

using namespace std;
int letter[256];

class Solution {
  public:
    int lengthOfLongestSubstring(string s) {
        fill(letter, letter + 256, 0);
        int begin = 0;
        int end = -1;
        int max_len = 0;
        while (true) {
            end++;
            if (end == s.size()) {
                break;
            }
            letter[s[end]]++;
            if (letter[s[end]] == 2) {
                while (letter[s[end]] == 2) {
                    letter[s[begin]]--;
                    begin++;
                }
            } else {
                if (end - begin + 1 > max_len) {
                    max_len = end - begin + 1;
                }
            }
        }
        return max_len;
    }
};

TEST_CASE() {
    Solution s;
    string str;

    str = "abcabcbb";
    REQUIRE(s.lengthOfLongestSubstring(str) == 3);
    str = "bbbbb";
    REQUIRE(s.lengthOfLongestSubstring(str) == 1);
    str = "pwwkew";
    REQUIRE(s.lengthOfLongestSubstring(str) == 3);
}