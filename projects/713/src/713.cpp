//
// Created by stellaura on 19/10/24.
//

#include <catch2/catch_all.hpp>
#include <limits>
#include <vector>

using namespace std;

class Solution {
  public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k) { return solution2(nums, k); }

    // 先算 >= 的个数，然后减去一下
    // 该方法统计的是 以固定左端点的 乘积>=k的个数
    int solution1(vector<int> &nums, int k) {
        // 去除掉无论如何都不可能有结果的内容 (空串都不满足)
        // 因此进入到else中的 至少串的长度为1
        if (k <= 1)
            return 0;

        int begin = 0;
        int end = -1;
        int product = 1;
        int count = 0;
        int size = nums.size();
        while (true) {
            if (product < k) {
                end++;
                if (end == size) {
                    break;
                }
                product *= nums[end];
            } else {
                count += size - end;
                product /= nums[begin];
                begin++;
            }
        }

        return size * (size + 1) / 2 - count;
    }

    // 该方法是统计 固定右端点，满足乘积<k的个数
    int solution2(vector<int> &nums, int k) {
        if (k <= 1)
            return 0;

        int begin = 0;
        int end = -1;
        int product = 1;
        int count = 0;
        int size = nums.size();
        while (true) {
            if (product < k) {
                count += end - begin + 1;
                end++;
                if (end == size) {
                    break;
                }
                product *= nums[end];
            } else {
                product /= nums[begin];
                begin++;
            }
        }

        return count;
    }
};

TEST_CASE() {
    Solution s{};
    SECTION("nums = [10,5,2,6], k = 100") {
        auto v = std::vector{10, 5, 2, 6};
        auto ret = s.numSubarrayProductLessThanK(v, 100);
        REQUIRE(ret == 8);
    }

    SECTION("nums = [1,2,3], k = 0") {
        auto v = std::vector{1, 2, 3};
        auto ret = s.numSubarrayProductLessThanK(v, 1);
        REQUIRE(ret == 0);
        ret = s.numSubarrayProductLessThanK(v, 0);
        REQUIRE(ret == 0);
        ret = s.numSubarrayProductLessThanK(v, 2);
        REQUIRE(ret == 1);
    }
}