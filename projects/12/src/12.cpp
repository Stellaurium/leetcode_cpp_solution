//
// Created by stellaura on 29/08/24.
//

#include <catch2/catch_all.hpp>
#include <string>

using namespace std;

char char_array[][3]{
    {' ', ' ', ' '}, // 占位符
    {'I', 'V', 'X'},
    {'X', 'L', 'C'},
    {'C', 'D', 'M'},
    {'M', ' ', ' '},
};

class Solution {
  public:
    string intToRoman(int num) { return intToRoman1(num); }

    // 我们可以看出来 罗马数字是十进制的
    // 我们每一个位数都可以通过罗马字母凑出来
    // 只不过他每一个数码上的数字的名称都不一样而以
    // 因此我们需要创建一个数码和数字的转换
    // 例如 order = 1  I V
    //     order = 2  X L
    //     order = 3  C D
    //     order = 4  M
    string intToRoman1(int num) {
        string roman = "";
        int num_array[4];
        // 首先算出num的位数
        int order = 0;
        while (num >= 1) {
            order++;
            num_array[order] = num % 10;
            num /= 10;
        }
        for (int i = order; i >= 1; i--) {
            int digit = num_array[i];
            if (digit == 9) {
                roman += char_array[i][0];
                roman += char_array[i][2];
            } else {
                if (digit >= 5) {
                    roman += char_array[i][1];
                    digit -= 5;
                }
                if (digit == 4) {
                    roman += char_array[i][0];
                    roman += char_array[i][1];
                } else {

                    for (int j = 0; j < digit; j++) {
                        roman += char_array[i][0];
                    }
                }
            }
        }
        return roman;
    }
};

TEST_CASE("Test Solution", "[roman]") {
    Solution s;
    REQUIRE(s.intToRoman(3) == "III");
    REQUIRE(s.intToRoman(4) == "IV");
    REQUIRE(s.intToRoman(9) == "IX");
    REQUIRE(s.intToRoman(58) == "LVIII");
    REQUIRE(s.intToRoman(1994) == "MCMXCIV");
    REQUIRE(s.intToRoman(3999) == "MMMCMXCIX");
    REQUIRE(s.intToRoman(3749) == "MMMDCCXLIX");
}