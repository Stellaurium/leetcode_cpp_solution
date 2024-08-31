//
// Created by stellaura on 29/08/24.
//

#include <catch2/catch_all.hpp>
#include <regex>
#include <string>

using namespace std;

// 字符          数值
// I             1
// V             5
// X             10
// L             50
// C             100
// D             500
// M             1000
enum class RomanNumeral { I, V, X, L, C, D, M, UNKNOWN };

std::map<RomanNumeral, int> romanToIntMap = {{RomanNumeral::I, 1},    {RomanNumeral::V, 5},      {RomanNumeral::X, 10},
                                             {RomanNumeral::L, 50},   {RomanNumeral::C, 100},    {RomanNumeral::D, 500},
                                             {RomanNumeral::M, 1000}, {RomanNumeral::UNKNOWN, 0}};

RomanNumeral getRomanNumeral(char c) {
    switch (c) {
    case 'I':
        return RomanNumeral::I;
    case 'V':
        return RomanNumeral::V;
    case 'X':
        return RomanNumeral::X;
    case 'L':
        return RomanNumeral::L;
    case 'C':
        return RomanNumeral::C;
    case 'D':
        return RomanNumeral::D;
    case 'M':
        return RomanNumeral::M;
    default:
        return RomanNumeral::UNKNOWN;
    }
}

// 通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。
//  数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。
//  同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
//     I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
//     X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
//     C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
//
//  即 罗马数字之后 1*10^k 5*10^k
//  1*10^k 可以写在 5*10^k 10*10^k 前表示负数

class Solution {
  public:
    // 每次读取两个字符
    // 看看顺序是否正确
    // 因此可以分辨出正负
    int romanToInt(string s) { return romanToInt2(s); }

    int romanToInt1(string s) {
        int length = s.length();
        int sum = 0;
        int i = 0;
        // 保证一定能读取两个字符
        while (i <= length - 2) {
            RomanNumeral c1 = getRomanNumeral(s[i]);
            RomanNumeral c2 = getRomanNumeral(s[i + 1]);
            if (romanToIntMap[c1] < romanToIntMap[c2]) {
                sum += romanToIntMap[c2] - romanToIntMap[c1];
                i += 2;
            } else {
                sum += romanToIntMap[c1];
                i++;
            }
        }
        if (i == length - 1) {
            sum += romanToIntMap[getRomanNumeral(s[i])];
        }
        return sum;
    }

    // 按照上面这个思路 更加奇技淫巧的方法
    int romanToInt2(string s) {
        // c++ 没有replace all
        // 只能用正则表达式

        s = std::regex_replace(s, std::regex("IV"), "1");
        s = std::regex_replace(s, std::regex("IX"), "2");
        s = std::regex_replace(s, std::regex("XL"), "3");
        s = std::regex_replace(s, std::regex("XC"), "4");
        s = std::regex_replace(s, std::regex("CD"), "5");
        s = std::regex_replace(s, std::regex("CM"), "6");

        int sum = 0;
        for (int i = 0; i < s.length(); i++) {
            switch (s[i]) {
            case 'I':
                sum += 1;
                break;
            case 'V':
                sum += 5;
                break;
            case 'X':
                sum += 10;
                break;
            case 'L':
                sum += 50;
                break;
            case 'C':
                sum += 100;
                break;
            case 'D':
                sum += 500;
                break;
            case 'M':
                sum += 1000;
                break;
            case '1':
                sum += 4;
                break;
            case '2':
                sum += 9;
                break;
            case '3':
                sum += 40;
                break;
            case '4':
                sum += 90;
                break;
            case '5':
                sum += 400;
                break;
            case '6':
                sum += 900;
                break;
            default:
                break;
            }
        }
        return sum;
    }
};

TEST_CASE("Roman to Integer", "[romanToInt]") {
    Solution s;
    REQUIRE(s.romanToInt("III") == 3);
    REQUIRE(s.romanToInt("IV") == 4);
    REQUIRE(s.romanToInt("IX") == 9);
    REQUIRE(s.romanToInt("LVIII") == 58);
    REQUIRE(s.romanToInt("MCMXCIV") == 1994);
}
