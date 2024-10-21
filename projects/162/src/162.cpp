//
// Created by stellaura on 19/10/24.
//
#include <catch2/catch_all.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    // 建议 二分法统一用左右闭区间
    // 左闭右开会导致mid向右偏移
    // 可能导致结果收敛的更大
    int findPeakElement(vector<int> &nums) { return solution4(nums); }

    int solution(vector<int> &nums) {
        // 假设 -1 和 size 位置为 -inf
        // 因为这个三分法 根本不需要两边的数值 仅仅只是一个标注
        // 因此可以一开始就是 -1 和 size
        int left = -1;
        int right = nums.size();
        // 至少四个元素
        // 这样可以保证推出循环之后 正好就剩下 left mid right 三个元素
        // 简易的证明
        // 当 4 个元素时 两种可能性都是 3
        // 当 > 4 的时候，两种可能性 至少 >= 3
        // 如果等于 3 返回，如果 >3 会重复上面的情况 直到为3
        while (right - left + 1 >= 4) {
            int left_mid = left + (right - left) / 2;
            int right_mid = left_mid + 1;
            if (nums[left_mid] < nums[right_mid]) {
                left = left_mid;
            } else {
                right = right_mid;
            }
        }
        return left + 1;
    }

    // 该方案只二分
    // 左闭右开
    // 左侧是峰顶左侧
    // 右侧是峰顶包括极值右侧
    int solution2(vector<int> &nums) {
        int left = 0, right = nums.size();
        // at least 2 elements
        while (right - left > 2) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[mid + 1]) {
                // nums[mid] 一定不是 可以从+1开始
                left = mid + 1;
            } else {
                // nums[mid + 1] 一定不是
                right = mid + 1;
            }
        }
        // now the size is <= 2
        // each edge can be treated as -inf
        // right-1 is the end of list
        if (nums[left] > nums[right - 1]) {
            return left;
        } else {
            return right - 1;
        }
    }

    // best solution
    int solution3(vector<int> &nums) {
        int left = 0, right = nums.size() - 1;
        // at least 1 elements
        // 收敛到 1个元素，然后不会到0个元素了 死循环
        // 这时 left right 都是同一个
        // 所以可以直接返回
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[mid + 1]) {
                // nums[mid] 一定不是 可以从+1开始
                left = mid + 1;
            } else {
                // nums[mid + 1] 一定不是
                right = mid;
            }
        }
        return left;
    }

    // template solution
    // 定义极大值及其右侧为blue
    int solution4(vector<int> &nums) {
        auto get = [&](int index) -> int {
            if (index == nums.size()) {
                return numeric_limits<int>::min();
            }
            return nums[index];
        };
        auto is_blue = [&](int index) -> bool {
            if (get(index) < get(index + 1)) {
                // index+1 可能是红也可能是蓝
                return false;
            } else {
                // index + 1 is blue
                // index is also blue
                return true;
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
        return left;
    }
};

TEST_CASE() {
    Solution s;
    vector<int> nums = {1, 2, 3, 1};
    REQUIRE(s.findPeakElement(nums) == 2);
    nums = {1, 2, 1, 3, 5, 6, 4};
    auto ret = s.findPeakElement(nums);
    REQUIRE(((ret == 1) || (ret == 5)));
    nums = {1};
    REQUIRE(s.findPeakElement(nums) == 0);
    nums = {1, 2};
    REQUIRE(s.findPeakElement(nums) == 1);
    nums = {4, 2};
    REQUIRE(s.findPeakElement(nums) == 0);
    nums = {4, 2, 3};
    REQUIRE((s.findPeakElement(nums) == 0 || s.findPeakElement(nums) == 2));
    nums = {4, 6, 3};
    REQUIRE(s.findPeakElement(nums) == 1);

    //    nums = {4,5,6,7,0,1,2};
    //    REQUIRE(s.findPeakElement(nums) == 3);
    //    nums = {2,4,5,6,7,8,9,10,0,1};
    //    REQUIRE(s.findPeakElement(nums) == 7);
}