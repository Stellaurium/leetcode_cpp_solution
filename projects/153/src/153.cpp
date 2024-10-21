//
// Created by stellaura on 20/10/24.
//
#include <catch2/catch_all.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    // return the value of min
    // not index of min
    int findMin(vector<int> &nums) { return solution2(nums); }

    // 显然 我们可以用 nums[0] or nums[-1] 来划分 两者的界限
    // 所有 >= nums[0] 的都在左侧
    // 所有 < nums[0] 的都在右侧
    // 第一个 < nums[0] 的就是最小值
    int solution(vector<int> &nums) {
        // 单调 or 只有一个元素
        if (nums[0] <= nums[nums.size() - 1]) {
            return nums[0];
        }

        int left = 0;
        int right = nums.size() - 1;
        int value = nums[0];
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < value) {
                // mid is in right
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return nums[left];
    }

    // 定义最小值及其右侧为blue
    int solution2(vector<int> &nums) {
        auto is_blue = [&](int index) {
            if (nums[index] < nums[0]) {
                return true;
            } else {
                return false;
            }
        };

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (is_blue(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (left == nums.size()) {
            return nums[0];
        } else {
            return nums[left];
        }
    }
};

TEST_CASE() {
    Solution s;
    vector<int> nums = {3, 4, 5, 1, 2};
    REQUIRE(s.findMin(nums) == 1);

    nums = {4, 5, 6, 7, 0, 1, 2};
    REQUIRE(s.findMin(nums) == 0);

    nums = {1, 2, 3, 4, 5, 6};
    REQUIRE(s.findMin(nums) == 1);

    nums = {1};
    REQUIRE(s.findMin(nums) == 1);
}