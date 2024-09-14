//
// Created by stellaura on 02/09/24.
//
#include "fast_and_slow_pointer.h"
#include <catch2/catch_all.hpp>
#include <vector>

void check_fast_and_slow(std::string &s) {
    int size = 0;
    int full_size = 0;
    size = s.size();
    full_size = fast_and_slow_pointer(s.begin(), s.end(), [](char c) { return isalpha(c); });
    REQUIRE(size == s.size());
    if (size != full_size) {
        // 需要防止最后一个字符是空 越界
        REQUIRE(s[full_size] == ' ');
    }
    REQUIRE(s[full_size - 1] != ' ');
}

TEST_CASE("Fast and Slow Pointer") {
    SECTION("String remove space") {
        std::string s1{" ab aa   bs   "};
        std::string s2{"ab aa   bs"};
        std::string s3{"abaabs"};
        std::string s4{"abaabs   "};
        std::string s5{"   abaabs"};
        std::string s6{"  abaabs  "};

        check_fast_and_slow(s1);
        check_fast_and_slow(s2);
        check_fast_and_slow(s3);
        check_fast_and_slow(s4);
        check_fast_and_slow(s5);
        check_fast_and_slow(s6);

        REQUIRE(s1 == "abaabs        ");
        REQUIRE(s2 == "abaabs    ");
        REQUIRE(s3 == "abaabs");
        REQUIRE(s4 == "abaabs   ");
        REQUIRE(s5 == "abaabs   ");
        REQUIRE(s6 == "abaabs    ");
    }

    SECTION("quick sort with pivot") {
        std::vector<int> v1{5, 6, 1, 3, 9, 7};
        fast_and_slow_pointer(v1.begin(), v1.end(), [](int n) { return n <= 5; });
        REQUIRE(v1 == std::vector<int>{5, 1, 3, 6, 9, 7});
    }

    SECTION("remove duplicates") {
        std::string s{"aabc"};
        char prev_value = '\0'; // 选一个第一个一定不会装的
        int end_index = fast_and_slow_pointer(
            s.begin(), s.end(), [&](char c) { return c != prev_value; },
            [&](char c) {
                prev_value = c;
                return c;
            });
        REQUIRE(s.substr(0, end_index) == "abc");

        s = "abbbbc";
        prev_value = '\0'; // 选一个第一个一定不会装的
        end_index = fast_and_slow_pointer(
            s.begin(), s.end(), [&](char c) { return c != prev_value; },
            [&](char c) {
                prev_value = c;
                return c;
            });
        REQUIRE(s.substr(0, end_index) == "abc");

        s = "abccccc";
        prev_value = '\0'; // 选一个第一个一定不会装的
        end_index = fast_and_slow_pointer(
            s.begin(), s.end(), [&](char c) { return c != prev_value; },
            [&](char c) {
                prev_value = c;
                return c;
            });
        REQUIRE(s.substr(0, end_index) == "abc");

        s = "aaabccccc";
        prev_value = '\0'; // 选一个第一个一定不会冲突的
        end_index = fast_and_slow_pointer(
            s.begin(), s.end(), [&](char c) { return c != prev_value; },
            [&](char c) {
                prev_value = c;
                return c;
            });
        REQUIRE(s.substr(0, end_index) == "abc");
    }
}
