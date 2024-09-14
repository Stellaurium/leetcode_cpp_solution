//
// Created by stellaura on 02/09/24.
//
#include "../projects/fast_and_slow_pointer/include/fast_and_slow_pointer.h"
#include <catch2/catch_all.hpp>
#include <string>

using namespace std;

class Solution {
  public:
    bool isPalindrome(string s) {
        int end = fast_and_slow_pointer(
            s.begin(), s.end(), [](char c) { return isalnum(c); },
            [](char c) { return std::tolower(c); });
        int begin = 0;
        end--;
        while (begin < end) {
            if (s[begin] != s[end]) {
                return false;
            }
            begin++;
            end--;
        }
        return true;
    }
};

TEST_CASE("Palindrome Number", "[isPalindrome]") {
    Solution s;
    REQUIRE(s.isPalindrome("A man, a plan, a canal: Panama") == true);
    REQUIRE(s.isPalindrome("race a car") == false);
    REQUIRE(s.isPalindrome("ara") == true);
    REQUIRE(s.isPalindrome(" ara ") == true);
    REQUIRE(s.isPalindrome("ara ") == true);
    REQUIRE(s.isPalindrome(" ara") == true);
    REQUIRE(s.isPalindrome(" ar a") == true);
    REQUIRE(s.isPalindrome("0P") == false);
}