//
// Created by stellaura on 03/09/24.
//
#include "../projects/fast_and_slow_pointer/include/fast_and_slow_pointer.h"

#include <algorithm>
#include <catch2/catch_all.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<vector<int>> threeSum(vector<int> &nums) { return double_pointer(nums); }

    // 由于可能出现重复
    // 每次 ++ 的时候 都需要判断跟上一个不一样
    vector<vector<int>> double_pointer(vector<int> &nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        int i = 0;
        while (i < nums.size() - 2) {
            int j = i + 1;
            int k = nums.size() - 1;
            while (j < k) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    ret.push_back({nums[i], nums[j], nums[k]});
                }
                // 边界情况
                // 如果和为0
                // 那么收缩哪边的边界都可以
                // 假设所有元素不一样
                // 如果收缩左边界 那么下一步和一定 > 0
                // 因此右边界还需要收缩
                // 此时都相当于左右都前进一步
                if (nums[i] + nums[j] + nums[k] < 0) {
                    j++;
                    while (j < nums.size() && nums[j] == nums[j - 1]) {
                        j++;
                    }
                } else {
                    k--;
                    while (k >= i && nums[k] == nums[k + 1]) {
                        k--;
                    }
                }
            }

            i++;
            while (i < nums.size() && nums[i] == nums[i - 1]) {
                i++;
            }
        }
        return ret;
    }

    // 使用快慢指针删掉重复元素
    // 这样是不行的
    // 因为最后答案可能类似于 -2 1 1
    // 这是正确答案 但是会因为 -1 的重复被删掉
    // 正确的就是 像上面一样 第一次初始化的时候 赋值
    // 然后++的时候跳过重复
    // 这样可以保证i j k 各自在其自身的范围内是不重复的
    // 但是他们相互之间可能重复
    // ERROR 错误的实现
    vector<vector<int>> double_pointer_remove_duplicate(vector<int> &nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());

        int prev_value = std::numeric_limits<int>::max();
        // 选一个第一个一定不会冲突的
        int size = fast_and_slow_pointer(
            nums.begin(), nums.end(), [&](auto c) { return c != prev_value; },
            [&](auto c) {
                prev_value = c;
                return c;
            });

        int i = 0;
        while (i < size - 2) {
            int j = i + 1;
            int k = size - 1;
            while (j < k) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    ret.push_back({nums[i], nums[j], nums[k]});
                }

                if (nums[i] + nums[j] + nums[k] < 0) {
                    j++;
                } else {
                    k--;
                }
            }

            i++;
        }
        return ret;
    }
};

TEST_CASE("test threeSum") {
    Solution s;
    vector<int> nums{-1, 0, 1, 2, -1, -4};
    s.threeSum(nums);
    REQUIRE(s.threeSum(nums) == vector<vector<int>>{{-1, -1, 2}, {-1, 0, 1}});
}
