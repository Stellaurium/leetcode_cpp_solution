//
// Created by stellaura on 02/09/24.
//

#pragma once

#include "../projects/rolling_hash/include/rolling_hash.h"
#include <string>
#include <vector>

namespace _implementation {

// https://oi-wiki.org/string/kmp/#%E6%9C%80%E7%BB%88%E7%AE%97%E6%B3%95
std::vector<int> _prefix_function(const std::string &s) {
    int n = s.length();
    std::vector<int> pi(n);
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
} // namespace _implementation

namespace string_matching {

int language_implement(const std::string &haystack, const std::string &needle) {
    auto ret = haystack.find(needle);
    if (ret == std::string::npos) {
        return -1;
    } else {
        return ret;
    }
}

int rolling_hash_implement(const std::string &haystack, const std::string &needle) {
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

int KMP_implement(const std::string &haystack, const std::string &needle) {
    if (needle.empty()) {
        return 0;
    }
    if (needle.size() > haystack.size()) {
        return -1;
    }
    auto jump = _implementation::_prefix_function(needle);
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

} // namespace string_matching
