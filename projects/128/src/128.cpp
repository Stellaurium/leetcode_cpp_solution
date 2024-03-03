//
// Created by stellaura on 02/03/24.
//
#include "catch2/catch_all.hpp"
#include <unordered_map>
#include <vector>
using namespace std;

// 方案一 效率不高
int longestConsecutive(vector<int> &&nums) {
    unordered_map<int, int> numMap;
    int maxLen = nums.empty() ? 0 : 1;

    // 将nums中的元素加入map，初始化长度为1
    for (int num : nums) {
        numMap[num] = 1;
    }

    bool flag = true; // 用于标记是否有更新
    while (flag) {
        flag = false; // 假设这一轮没有更新
        for (auto &entry : numMap) {
            int key = entry.first;
            if (numMap.find(key + 1) != numMap.end()) { // 如果key+1存在
                int newLen = 1 + numMap[key + 1];
                if (newLen > numMap[key]) { // 只有当新长度大于当前长度时才更新
                    numMap[key] = newLen;
                    // 标记有更新
                    flag = true;
                    // 更新最大长度
                    if (newLen > maxLen) {
                        maxLen = newLen;
                    }
                }
            }
        }
    }

    return maxLen;
}

TEST_CASE("Inefficient way", "[slow]") {

    REQUIRE(4 == longestConsecutive(std::vector{100, 4, 200, 1, 3, 2}));
    REQUIRE(9 == longestConsecutive(std::vector{0, 3, 7, 2, 5, 8, 4, 6, 0, 1}));
    REQUIRE(0 == longestConsecutive(std::vector<int>{}));
    REQUIRE(1 == longestConsecutive(std::vector<int>{0}));
}