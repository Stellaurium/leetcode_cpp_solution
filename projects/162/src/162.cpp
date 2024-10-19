//
// Created by stellaura on 19/10/24.
//
#include <catch2/catch_all.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    int findPeakElement(vector<int> &nums) { return solution(nums); }

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
        return left+1;
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
    nums = {1,2};
    REQUIRE(s.findPeakElement(nums) == 1);
    nums = {4,2};
    REQUIRE(s.findPeakElement(nums) == 0);
    nums = {4,2,3};
    REQUIRE((s.findPeakElement(nums) == 0||s.findPeakElement(nums) == 2));
    nums = {4,6,3};
    REQUIRE(s.findPeakElement(nums) == 1);
}