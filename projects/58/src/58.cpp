//
// Created by stellaura on 31/08/24.
//
#include <catch2/catch_all.hpp>
#include <cctype>
#include <string>

using namespace std;

class Solution {
  public:
    int lengthOfLastWord(string s) {
        int count = 0;
        bool is_met_letter = false;
        for (auto it = s.rbegin(); it != s.rend(); ++it) {

            if (isalpha(*it)) {
                count++;
                is_met_letter = true;
            }
            else if (is_met_letter) {
                break;
            }
        }
        return count;
    }
};

TEST_CASE("Test Solution lengthOfLastWord function", "[lengthOfLastWord]") {
    Solution solution;
    REQUIRE(solution.lengthOfLastWord("Hello World") == 5);
    REQUIRE(solution.lengthOfLastWord("a ") == 1);
}