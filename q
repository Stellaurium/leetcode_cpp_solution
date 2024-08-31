[1mdiff --git a/projects/12/src/12.cpp b/projects/12/src/12.cpp[m
[1mindex 77ebc7e..2931a87 100644[m
[1m--- a/projects/12/src/12.cpp[m
[1m+++ b/projects/12/src/12.cpp[m
[36m@@ -1,3 +1,74 @@[m
 //[m
 // Created by stellaura on 29/08/24.[m
 //[m
[32m+[m
[32m+[m[32m#include <catch2/catch_all.hpp>[m
[32m+[m[32m#include <string>[m
[32m+[m
[32m+[m[32musing namespace std;[m
[32m+[m
[32m+[m[32mchar char_array[][3]{[m
[32m+[m[32m    {' ', ' ', ' '}, // 占位符[m
[32m+[m[32m    {'I', 'V', 'X'},[m
[32m+[m[32m    {'X', 'L', 'C'},[m
[32m+[m[32m    {'C', 'D', 'M'},[m
[32m+[m[32m    {'M', ' ', ' '},[m
[32m+[m[32m};[m
[32m+[m
[32m+[m[32mclass Solution {[m
[32m+[m[32m  public:[m
[32m+[m[32m    string intToRoman(int num) { return intToRoman1(num); }[m
[32m+[m
[32m+[m[32m    // 我们可以看出来 罗马数字是十进制的[m
[32m+[m[32m    // 我们每一个位数都可以通过罗马字母凑出来[m
[32m+[m[32m    // 只不过他每一个数码上的数字的名称都不一样而以[m
[32m+[m[32m    // 因此我们需要创建一个数码和数字的转换[m
[32m+[m[32m    // 例如 order = 1  I V[m
[32m+[m[32m    //     order = 2  X L[m
[32m+[m[32m    //     order = 3  C D[m
[32m+[m[32m    //     order = 4  M[m
[32m+[m[32m    string intToRoman1(int num) {[m
[32m+[m[32m        string roman = "";[m
[32m+[m[32m        int num_array[4];[m
[32m+[m[32m        // 首先算出num的位数[m
[32m+[m[32m        int order = 0;[m
[32m+[m[32m        while (num >= 1) {[m
[32m+[m[32m            order++;[m
[32m+[m[32m            num_array[order] = num % 10;[m
[32m+[m[32m            num /= 10;[m
[32m+[m[32m        }[m
[32m+[m[32m        for (int i = order; i >= 1; i--) {[m
[32m+[m[32m            int digit = num_array[i];[m
[32m+[m[32m            if (digit == 9) {[m
[32m+[m[32m                roman += char_array[i][0];[m
[32m+[m[32m                roman += char_array[i][2];[m
[32m+[m[32m            } else {[m
[32m+[m[32m                if (digit >= 5) {[m
[32m+[m[32m                    roman += char_array[i][1];[m
[32m+[m[32m                    digit -= 5;[m
[32m+[m[32m                }[m
[32m+[m[32m                if (digit == 4) {[m
[32m+[m[32m                    roman += char_array[i][0];[m
[32m+[m[32m                    roman += char_array[i][1];[m
[32m+[m[32m                } else {[m
[32m+[m
[32m+[m[32m                    for (int j = 0; j < digit; j++) {[m
[32m+[m[32m                        roman += char_array[i][0];[m
[32m+[m[32m                    }[m
[32m+[m[32m                }[m
[32m+[m[32m            }[m
[32m+[m[32m        }[m
[32m+[m[32m        return roman;[m
[32m+[m[32m    }[m
[32m+[m[32m};[m
[32m+[m
[32m+[m[32mTEST_CASE("Test Solution", "[roman]") {[m
[32m+[m[32m    Solution s;[m
[32m+[m[32m    REQUIRE(s.intToRoman(3) == "III");[m
[32m+[m[32m    REQUIRE(s.intToRoman(4) == "IV");[m
[32m+[m[32m    REQUIRE(s.intToRoman(9) == "IX");[m
[32m+[m[32m    REQUIRE(s.intToRoman(58) == "LVIII");[m
[32m+[m[32m    REQUIRE(s.intToRoman(1994) == "MCMXCIV");[m
[32m+[m[32m    REQUIRE(s.intToRoman(3999) == "MMMCMXCIX");[m
[32m+[m[32m    REQUIRE(s.intToRoman(3749) == "MMMDCCXLIX");[m
[32m+[m[32m}[m
\ No newline at end of file[m
[1mdiff --git a/projects/13/src/13.cpp b/projects/13/src/13.cpp[m
[1mindex 77ebc7e..8fe68d7 100644[m
[1m--- a/projects/13/src/13.cpp[m
[1m+++ b/projects/13/src/13.cpp[m
[36m@@ -1,3 +1,154 @@[m
 //[m
 // Created by stellaura on 29/08/24.[m
 //[m
[32m+[m
[32m+[m[32m#include <catch2/catch_all.hpp>[m
[32m+[m[32m#include <regex>[m
[32m+[m[32m#include <string>[m
[32m+[m
[32m+[m[32musing namespace std;[m
[32m+[m
[32m+[m[32m// 字符          数值[m
[32m+[m[32m// I             1[m
[32m+[m[32m// V             5[m
[32m+[m[32m// X             10[m
[32m+[m[32m// L             50[m
[32m+[m[32m// C             100[m
[32m+[m[32m// D             500[m
[32m+[m[32m// M             1000[m
[32m+[m[32menum class RomanNumeral { I, V, X, L, C, D, M, UNKNOWN };[m
[32m+[m
[32m+[m[32mstd::map<RomanNumeral, int> romanToIntMap = {{RomanNumeral::I, 1},    {RomanNumeral::V, 5},      {RomanNumeral::X, 10},[m
[32m+[m[32m                                             {RomanNumeral::L, 50},   {RomanNumeral::C, 100},    {RomanNumeral::D, 500},[m
[32m+[m[32m                                             {RomanNumeral::M, 1000}, {RomanNumeral::UNKNOWN, 0}};[m
[32m+[m
[32m+[m[32mRomanNumeral getRomanNumeral(char c) {[m
[32m+[m[32m    switch (c) {[m
[32m+[m[32m    case 'I':[m
[32m+[m[32m        return RomanNumeral::I;[m
[32m+[m[32m    case 'V':[m
[32m+[m[32m        return RomanNumeral::V;[m
[32m+[m[32m    case 'X':[m
[32m+[m[32m        return RomanNumeral::X;[m
[32m+[m[32m    case 'L':[m
[32m+[m[32m        return RomanNumeral::L;[m
[32m+[m[32m    case 'C':[m
[32m+[m[32m        return RomanNumeral::C;[m
[32m+[m[32m    case 'D':[m
[32m+[m[32m        return RomanNumeral::D;[m
[32m+[m[32m    case 'M':[m
[32m+[m[32m        return RomanNumeral::M;[m
[32m+[m[32m    default:[m
[32m+[m[32m        return RomanNumeral::UNKNOWN;[m
[32m+[m[32m    }[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// 通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。[m
[32m+[m[32m//  数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。[m
[32m+[m[32m//  同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：[m
[32m+[m[32m//     I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。[m
[32m+[m[32m//     X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。[m
[32m+[m[32m//     C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。[m
[32m+[m[32m//[m
[32m+[m[32m//  即 罗马数字之后 1*10^k 5*10^k[m
[32m+[m[32m//  1*10^k 可以写在 5*10^k 10*10^k 前表示负数[m
[32m+[m
[32m+[m[32mclass Solution {[m
[32m+[m[32m  public:[m
[32m+[m[32m    // 每次读取两个字符[m
[32m+[m[32m    // 看看顺序是否正确[m
[32m+[m[32m    // 因此可以分辨出正负[m
[32m+[m[32m    int romanToInt(string s) { return romanToInt2(s); }[m
[32m+[m
[32m+[m[32m    int romanToInt1(string s) {[m
[32m+[m[32m        int length = s.length();[m
[32m+[m[32m        int sum = 0;[m
[32m+[m[32m        int i = 0;[m
[32m+[m[32m        // 保证一定能读取两个字符[m
[32m+[m[32m        while (i <= length - 2) {[m
[32m+[m[32m            RomanNumeral c1 = getRomanNumeral(s[i]);[m
[32m+[m[32m            RomanNumeral c2 = getRomanNumeral(s[i + 1]);[m
[32m+[m[32m            if (romanToIntMap[c1] < romanToIntMap[c2]) {[m
[32m+[m[32m                sum += romanToIntMap[c2] - romanToIntMap[c1];[m
[32m+[m[32m                i += 2;[m
[32m+[m[32m            } else {[m
[32m+[m[32m                sum += romanToIntMap[c1];[m
[32m+[m[32m                i++;[m
[32m+[m[32m            }[m
[32m+[m[32m        }[m
[32m+[m[32m        if (i == length - 1) {[m
[32m+[m[32m            sum += romanToIntMap[getRomanNumeral(s[i])];[m
[32m+[m[32m        }[m
[32m+[m[32m        return sum;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    // 按照上面这个思路 更加奇技淫巧的方法[m
[32m+[m[32m    int romanToInt2(string s) {[m
[32m+[m[32m        // c++ 没有replace all[m
[32m+[m[32m        // 只能用正则表达式[m
[32m+[m
[32m+[m[32m        s = std::regex_replace(s, std::regex("IV"), "1");[m
[32m+[m[32m        s = std::regex_replace(s, std::regex("IX"), "2");[m
[32m+[m[32m        s = std::regex_replace(s, std::regex("XL"), "3");[m
[32m+[m[32m        s = std::regex_replace(s, std::regex("XC"), "4");[m
[32m+[m[32m        s = std::regex_replace(s, std::regex("CD"), "5");[m
[32m+[m[32m        s = std::regex_replace(s, std::regex("CM"), "6");[m
[32m+[m
[32m+[m[32m        int sum = 0;[m
[32m+[m[32m        for (int i = 0; i < s.length(); i++) {[m
[32m+[m[32m            switch (s[i]) {[m
[32m+[m[32m            case 'I':[m
[32m+[m[32m                sum += 1;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case 'V':[m
[32m+[m[32m                sum += 5;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case 'X':[m
[32m+[m[32m                sum += 10;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case 'L':[m
[32m+[m[32m                sum += 50;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case 'C':[m
[32m+[m[32m                sum += 100;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case 'D':[m
[32m+[m[32m                sum += 500;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case 'M':[m
[32m+[m[32m                sum += 1000;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case '1':[m
[32m+[m[32m                sum += 4;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case '2':[m
[32m+[m[32m                sum += 9;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case '3':[m
[32m+[m[32m                sum += 40;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case '4':[m
[32m+[m[32m                sum += 90;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case '5':[m
[32m+[m[32m                sum += 400;[m
[32m+[m[32m                break;[m
[32m+[m[32m            case '6':[m
[32m+[m[32m                sum += 900;[m
[32m+[m[32m                break;[m
[32m+[m[32m            default:[m
[32m+[m[32m                break;[m
[32m+[m[32m            }[m
[32m+[m[32m        }[m
[32m+[m[32m        return sum;[m
[32m+[m[32m    }[m
[32m+[m[32m};[m
[32m+[m
[32m+[m[32mTEST_CASE("Roman to Integer", "[romanToInt]") {[m
[32m+[m[32m    Solution s;[m
[32m+[m[32m    REQUIRE(s.romanToInt("III") == 3);[m
[32m+[m[32m    REQUIRE(s.romanToInt("IV") == 4);[m
[32m+[m[32m    REQUIRE(s.romanToInt("IX") == 9);[m
[32m+[m[32m    REQUIRE(s.romanToInt("LVIII") == 58);[m
[32m+[m[32m    REQUIRE(s.romanToInt("MCMXCIV") == 1994);[m
[32m+[m[32m}[m
[1mdiff --git a/projects/1438/src/1438.cpp b/projects/1438/src/1438.cpp[m
[1mindex 542ed55..b6e3640 100644[m
[1m--- a/projects/1438/src/1438.cpp[m
[1m+++ b/projects/1438/src/1438.cpp[m
[36m@@ -1,3 +1,93 @@[m
 //[m
 // Created by stellaura on 31/08/24.[m
 //[m
[32m+[m[32m#include <catch2/catch_all.hpp>[m
[32m+[m[32m#include <deque>[m
[32m+[m[32m#include <functional>[m
[32m+[m[32m#include <vector>[m
[32m+[m
[32m+[m[32musing namespace std;[m
[32m+[m
[32m+[m[32m// 天津大学 预推免第四题[m
[32m+[m[32m// 知道应该使用 单调队列 但是差一点点[m
[32m+[m[32m// 最后五分钟想出来了 都晚了[m
[32m+[m
[32m+[m[32m// min-queue 使用 less[m
[32m+[m[32mvoid pushMonotoneQueue(deque<pair<int, int>> &q, const std::function<bool(int, int)> &comp, int num, int index) {[m
[32m+[m[32m    while (!q.empty() && comp(q.back().first, num)) {[m
[32m+[m[32m        q.pop_back();[m
[32m+[m[32m    }[m
[32m+[m[32m    q.emplace_back(num, index);[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// 电调队列可以用 O(1) 的时间 获取一个区间内的极值[m
[32m+[m[32mclass Solution {[m
[32m+[m[32m  public:[m
[32m+[m[32m    int longestSubarray(vector<int> &nums, int limit) {[m
[32m+[m[32m        deque<pair<int, int>> min_q;[m
[32m+[m[32m        deque<pair<int, int>> max_q;[m
[32m+[m[32m        int begin = 0;[m
[32m+[m[32m        int end = 0;[m
[32m+[m[32m        int max_length = 0;[m
[32m+[m
[32m+[m[32m        for (end = 0; end < nums.size(); end++) {[m
[32m+[m[32m            pushMonotoneQueue(min_q, greater_equal<int>(), nums[end], end);[m
[32m+[m[32m            pushMonotoneQueue(max_q, less_equal<int>(), nums[end], end);[m
[32m+[m
[32m+[m[32m            // 该区间肯定不行了 同时 end不管怎么++也不可能是正确答案了[m
[32m+[m[32m            // 因此剪枝end后面的[m
[32m+[m[32m            // 让begin++[m
[32m+[m[32m            // 因为现在是不满足的 但是刚才满足[m
[32m+[m[32m            // 因此添加了 当前元素后 一定改变了 min 或者 max[m
[32m+[m[32m            // 我们可以比较 min_q.front().second 和 max_q.front().second[m
[32m+[m[32m            // 大的那个一定就是刚才刚插入的元素[m
[32m+[m[32m            // 其他另一个队列中的所有元素都一定是当前元素的index小的[m
[32m+[m[32m            // 因此只需要不断pop front 另一个队列[m
[32m+[m[32m            // 直到刚好不满足那个极值的后面一个元素[m
[32m+[m[32m            int last_extremum_index = 0;[m
[32m+[m[32m            if (max_q.front().first - min_q.front().first > limit) {[m
[32m+[m
[32m+[m[32m                if (min_q.front().second < max_q.front().second) {[m
[32m+[m[32m                    // pop min[m
[32m+[m[32m                    // 需要确保不会弹空[m
[32m+[m[32m                    // 但是因为不管插入什么 这个元素一定会在两个队列的底部[m
[32m+[m[32m                    // 两者的插值必定是0 满足limit[m
[32m+[m[32m                    // 所以队列永远不会空[m
[32m+[m[32m                    // while (!min_q.empty() && max_q.front().first - min_q.front().first > limit){[m
[32m+[m[32m                    while (max_q.front().first - min_q.front().first > limit) {[m
[32m+[m[32m                        last_extremum_index = min_q.front().second;[m
[32m+[m[32m                        min_q.pop_front();[m
[32m+[m[32m                    }[m
[32m+[m[32m                } else {[m
[32m+[m[32m                    // pop max[m
[32m+[m[32m                    while (max_q.front().first - min_q.front().first > limit) {[m
[32m+[m[32m                        last_extremum_index = max_q.front().second;[m
[32m+[m[32m                        max_q.pop_front();[m
[32m+[m[32m                    }[m
[32m+[m[32m                }[m
[32m+[m[32m                begin = last_extremum_index + 1;[m
[32m+[m[32m            }[m
[32m+[m
[32m+[m[32m            if (end - begin + 1 > max_length) {[m
[32m+[m[32m                max_length = end - begin + 1;[m
[32m+[m[32m            }[m
[32m+[m[32m        }[m
[32m+[m[32m        return max_length;[m
[32m+[m[32m    }[m
[32m+[m[32m};[m
[32m+[m
[32m+[m[32mTEST_CASE("test longestSubarray") {[m
[32m+[m[32m    Solution s;[m
[32m+[m
[32m+[m[32m    vector<int> nums{10, 1, 2, 4, 7, 2};[m
[32m+[m[32m    int result = s.longestSubarray(nums, 5);[m
[32m+[m[32m    REQUIRE(result == 4);[m
[32m+[m
[32m+[m[32m    vector<int> nums2{4, 2, 2, 2, 4, 4, 2, 2};[m
[32m+[m[32m    int result2 = s.longestSubarray(nums2, 0);[m
[32m+[m[32m    REQUIRE(result2 == 3);[m
[32m+[m
[32m+[m[32m    vector<int> nums3{4, 2, 100, 2, 4, 4, 2, 2, 2};[m
[32m+[m[32m    int result3 = s.longestSubarray(nums3, 0);[m
[32m+[m[32m    REQUIRE(result3 == 3);[m
[32m+[m[32m}[m
[1mdiff --git a/projects/92/src/92.cpp b/projects/92/src/92.cpp[m
[1mindex e69de29..61dae23 100644[m
[1m--- a/projects/92/src/92.cpp[m
[1m+++ b/projects/92/src/92.cpp[m
[36m@@ -0,0 +1,24 @@[m
[32m+[m[32m#include <catch2/catch_all.hpp>[m
[32m+[m
[32m+[m[32mstruct ListNode {[m
[32m+[m[32m    int val;[m
[32m+[m[32m    ListNode *next;[m
[32m+[m[32m    ListNode() : val(0), next(nullptr) {}[m
[32m+[m[32m    ListNode(int x) : val(x), next(nullptr) {}[m
[32m+[m[32m    ListNode(int x, ListNode *next) : val(x), next(next) {}[m
[32m+[m[32m};[m
[32m+[m
[32m+[m[32mclass Solution {[m
[32m+[m[32m  public:[m
[32m+[m[32m    ListNode *reverseBetween(ListNode *head, int left, int right) {[m
[32m+[m[32m        ListNode *node0 = new ListNode(0);[m
[32m+[m[32m        ListNode *current = node0;[m
[32m+[m[32m        node0->next = head;[m
[32m+[m
[32m+[m[32m        int index = 0;[m
[32m+[m[32m        while (index != left - 1) {[m
[32m+[m[32m            index++;[m
[32m+[m[32m            current = current->next;[m
[32m+[m[32m        }[m
[32m+[m[32m    }[m
[32m+[m[32m};[m
\ No newline at end of file[m
