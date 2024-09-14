//
// Created by stellaura on 02/09/24.
//
#include "string_matching.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Rolling Hash Solution", "[rolling_hash]") {
    REQUIRE(string_matching::rolling_hash_implement("hello", "ll") == 2);
    REQUIRE(string_matching::rolling_hash_implement("aaaaa", "bba") == -1);
    REQUIRE(string_matching::rolling_hash_implement("", "") == 0);
    REQUIRE(string_matching::rolling_hash_implement("aaa", "aaaaaa") == -1);
    REQUIRE(string_matching::rolling_hash_implement("aaa", "aaa") == 0);
    REQUIRE(string_matching::rolling_hash_implement("aaa", "") == 0);
    REQUIRE(string_matching::rolling_hash_implement("aabaaabaaac", "aabaaac") == 4);
}

TEST_CASE("KMP Solution", "[kmp]") {
    REQUIRE(string_matching::KMP_implement("abababcaa", "ababc") == 2);
    REQUIRE(string_matching::KMP_implement("hello", "ll") == 2);
    REQUIRE(string_matching::KMP_implement("aaaaa", "bba") == -1);
    REQUIRE(string_matching::KMP_implement("", "") == 0);
    REQUIRE(string_matching::KMP_implement("aaa", "aaaaaa") == -1);
    REQUIRE(string_matching::KMP_implement("aaa", "aaa") == 0);
    REQUIRE(string_matching::KMP_implement("aaa", "") == 0);
    REQUIRE(string_matching::KMP_implement("aabaaabaaac", "aabaaac") == 4);
}

TEST_CASE("KMP initial", "[KMP_initial]") {
    REQUIRE(_implementation::_prefix_function("ababa") == std::vector<int>{0, 0, 1, 2, 3});
    REQUIRE(_implementation::_prefix_function("ababc") == std::vector<int>{0, 0, 1, 2, 0});
    REQUIRE(_implementation::_prefix_function("abcabcabc") == std::vector<int>{0, 0, 0, 1, 2, 3, 4, 5, 6});
    REQUIRE(_implementation::_prefix_function("aabaaac") == std::vector<int>{0, 1, 0, 1, 2, 2, 0});
}
