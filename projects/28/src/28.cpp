//
// Created by stellaura on 31/08/24.
//
#include <catch2/catch_all.hpp>
#include <string>

using namespace std;

// 字符串匹配
// GPT给的：
// 朴素算法：简单但效率低，适用于小规模匹配。
// KMP算法：经典高效，适合一般的模式匹配。
// Rabin-Karp算法：通过哈希优化匹配，但哈希冲突会导致性能下降。
// Boyer-Moore和Sunday算法：适合较大文本，尤其是含有大量不匹配的字符时。
// Aho-Corasick算法：非常适合多模式匹配问题。
// Z算法：适合快速模式匹配和重复模式检测。
// Suffix Array & LCP：适合处理大量查询和后缀问题。
class Solution {
  public:
    int strStr(string haystack, string needle) { languageImplement(haystack, needle); }

    int languageImplement(string &haystack, string &needle) {
        auto ret = haystack.find(needle);
        if (ret == string::npos) {
            return -1;
        } else {
            return ret;
        }
    }

    int KMP(string &haystack, string &needle){

    }

    int rollingHash(string &haystack, string &needle){

    }

};

TEST_CASE("Test Solution", "[strStr]") {
    Solution s;
    REQUIRE(s.strStr("hello", "ll") == 2);
    REQUIRE(s.strStr("aaaaa", "bba") == -1);
    REQUIRE(s.strStr("", "") == 0);
}