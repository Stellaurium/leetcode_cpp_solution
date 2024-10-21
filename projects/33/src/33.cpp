//
// Created by stellaura on 20/10/24.
//
#include <catch2/catch_all.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    int search(vector<int> &nums, int target) { return solution3(nums, target); }

    // 可以利用 153的结果
    // 首先找到分界线，然后二分
    int solution1(vector<int> &nums, int target) {
        auto find_in_range = [&](auto begin, auto end) -> int {
            auto it = lower_bound(begin, end, target);
            if (it == nums.end() || *it != target) {
                return -1;
            } else {
                return it - nums.begin();
            }
        };

        // 单调 or 只有一个元素
        if (nums[0] <= nums[nums.size() - 1]) {
            find_in_range(nums.begin(), nums.end());
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

        if (nums[0] <= target) {
            return find_in_range(nums.begin(), nums.begin() + left);
        } else {
            return find_in_range(nums.begin() + left, nums.end());
        }
    }

    // 仅仅使用一次二分
    // 染色的条件是
    // 分类讨论两种情况，target在左侧或者右侧
    int solution2(vector<int> &nums, int target) {

        int left = 0;
        int right = nums.size() - 1;

        if (nums[0] <= target) {
            while (left <= right) {
                auto mid = left + (right - left) / 2;
                if (nums[mid] == target) {
                    return mid;
                } else if (nums[mid] > target) {
                    // 一定在 左侧
                    right = mid - 1;
                } else {
                    if (nums[0] <= nums[mid]) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
            }
        } else {
            while (left <= right) {
                auto mid = left + (right - left) / 2;
                if (nums[mid] == target) {
                    return mid;
                } else if (nums[mid] < target) {
                    left = mid + 1;
                } else {
                    if (nums[0] <= nums[mid]) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
            }
        }
        return -1;
    }

    // best solution
    // standard template
    int solution3(vector<int> &nums, int target) {
        auto is_blue = [&](int index) {
            if (target >= nums[0]) {
                return nums[index] >= target || nums[index] < nums[0];
            } else {
                return nums[index] >= target && nums[index] < nums[0];
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
            return -1;
        } else {
            return left;
        }
    }
};

TEST_CASE() {
    Solution s;

    vector<int> nums;
    int target;
    int result;

    nums = {1, 3};
    target = 1;
    result = s.search(nums, target);
    REQUIRE(result == 0);

    nums = {4, 5, 6, 7, 0, 1, 2};
    target = 0;
    result = s.search(nums, target);
    REQUIRE(result == 4);

    nums = {4, 5, 6, 7, 0, 1, 2};
    target = 1;
    result = s.search(nums, target);
    REQUIRE(result == 5);

    nums = {4, 5, 6, 7, 0, 1, 2};
    target = 2;
    result = s.search(nums, target);
    REQUIRE(result == 6);

    nums = {4, 5, 6, 7, 0, 1, 2};
    target = 5;
    result = s.search(nums, target);
    REQUIRE(result == 1);

    nums = {4, 5, 6, 7, 0, 1, 2};
    target = 3;
    result = s.search(nums, target);
    REQUIRE(result == -1);

    nums = {1};
    target = 1;
    result = s.search(nums, target);
    REQUIRE(result == 0);

    nums = {1};
    target = 0;
    result = s.search(nums, target);
    REQUIRE(result == -1);

    nums = {1, 2, 3};
    target = 1;
    result = s.search(nums, target);
    REQUIRE(result == 0);

    nums = {1, 2, 3};
    target = 2;
    result = s.search(nums, target);
    REQUIRE(result == 1);

    nums = {1, 2, 3};
    target = 3;
    result = s.search(nums, target);
    REQUIRE(result == 2);
}