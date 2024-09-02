//
// Created by stellaura on 31/08/24.
//
#include "../projects/rolling_hash/include/rolling_hash.h"
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
    int strStr(string haystack, string needle) { return rollingHash(haystack, needle); }

    int languageImplement(const string &haystack, const string &needle) {
        auto ret = haystack.find(needle);
        if (ret == string::npos) {
            return -1;
        } else {
            return ret;
        }
    }

    int rollingHash(const string &haystack, const string &needle) {
        if (needle.empty()) {
            return 0;
        }
        if (needle.size() > haystack.size()) {
            return -1;
        }

        int base = 256;
        int mod = 1000000007;
        RollingHashWithString<char> target(needle, base, mod);
        RollingHashWithString<char> source(haystack, base, mod);

        for (int i = 0; i < needle.size(); i++) {
            target.back_go_forward();
            source.back_go_forward();
        }

        int end = needle.size() - 1;
        while (end != haystack.size()) {
            if (target.get_hash() == source.get_hash()) {
                return end - needle.size() + 1;
            }

            source.back_go_forward();
            source.front_go_forward();
            end++;
        }

        return -1;
    }

    // 核心思想是 在你匹配的过程中
    // 一旦发现不匹配
    // 传统的方式是移动一个
    // 但是这时候实际上你已经知道了这两个字符串前面的部分完全匹配
    // 因此你可以跳过多个字符
    // 直到前面的部分可能匹配
    // 而与处理过程就是 描述 在已经匹配了这么多的情况下 可以跳多少个字符
    int KMP(const string &haystack, const string &needle) {
        if (needle.empty()) {
            return 0;
        }
        if (needle.size() > haystack.size()) {
            return -1;
        }
        auto jump = _prefix_function(needle);
        int index = 0;
        int needle_index = 0;
        while (index < haystack.size()) {
            if (haystack[index] == needle[needle_index]) {
                index++;
                needle_index++;
                if (needle_index == needle.size()) {
                    return index - needle.size();
                }
            } else {
                if (needle_index == 0) {
                    // 开始就不匹配
                    // 两者都不匹配 index向前一个 needle_index 向前一个
                    index++;
                } else {
                    needle_index = jump[needle_index - 1];
                }
            }
        }
        return -1;
    }

    // https://oi-wiki.org/string/kmp/#%E6%9C%80%E7%BB%88%E7%AE%97%E6%B3%95
    vector<int> _prefix_function(const string &s) {
        int n = s.length();
        vector<int> pi(n);
        // pi[0] = 0;
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            // 不断寻找可能的最长的前后缀
            while (j > 0 && s[i] != s[j])
                j = pi[j - 1];
            // 当匹配到了之后 j就是字符串的最后
            // 需要++返回长度
            // 如果 s[i] != s[j] j==0 就根本没有找到
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return pi;
    }
};

TEST_CASE("Rolling Hash Solution", "[rolling_hash]") {
    Solution s;
    REQUIRE(s.rollingHash("hello", "ll") == 2);
    REQUIRE(s.rollingHash("aaaaa", "bba") == -1);
    REQUIRE(s.rollingHash("", "") == 0);
    REQUIRE(s.rollingHash("aaa", "aaaaaa") == -1);
    REQUIRE(s.rollingHash("aaa", "aaa") == 0);
    REQUIRE(s.rollingHash("aaa", "") == 0);
    REQUIRE(s.rollingHash("aabaaabaaac", "aabaaac") == 4);
}

TEST_CASE("KMP Solution", "[kmp]") {
    Solution s;
    REQUIRE(s.KMP("abababcaa", "ababc") == 2);
    REQUIRE(s.KMP("hello", "ll") == 2);
    REQUIRE(s.KMP("aaaaa", "bba") == -1);
    REQUIRE(s.KMP("", "") == 0);
    REQUIRE(s.KMP("aaa", "aaaaaa") == -1);
    REQUIRE(s.KMP("aaa", "aaa") == 0);
    REQUIRE(s.KMP("aaa", "") == 0);
    REQUIRE(s.KMP("aabaaabaaac", "aabaaac") == 4);
}

TEST_CASE("KMP initial", "[KMP_initial]") {
    Solution s;
    REQUIRE(s._prefix_function("ababa") == std::vector<int>{0, 0, 1, 2, 3});
    REQUIRE(s._prefix_function("ababc") == std::vector<int>{0, 0, 1, 2, 0});
    REQUIRE(s._prefix_function("abcabcabc") == std::vector<int>{0, 0, 0, 1, 2, 3, 4, 5, 6});
    REQUIRE(s._prefix_function("aabaaac") == std::vector<int>{0, 1, 0, 1, 2, 2, 0});
}
