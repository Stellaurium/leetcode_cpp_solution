//
// Created by stellaura on 19/10/24.
//

#include <algorithm>
#include <catch2/catch_all.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> searchRange(vector<int> &nums, int target) {
        auto end = std::upper_bound(nums.begin(), nums.end(), target);
        auto begin = std::lower_bound(nums.begin(), nums.end(), target);
        vector<int> ret;
        if (end - begin == 0) {
            return {-1, -1};
        }
        ret.push_back(int(begin - nums.begin()));
        ret.push_back(int(end - nums.begin()) - 1);
        return ret;
    }
};

TEST_CASE() {
    Solution s;
    vector<int> nums = {5, 7, 7, 8, 8, 10, 10};
    vector<int> ret = s.searchRange(nums, 8);
    REQUIRE(ret == vector<int>{3, 4});
    ret = s.searchRange(nums, 6);
    REQUIRE(ret == vector<int>{-1, -1});
    ret = s.searchRange(nums, 5);
    REQUIRE(ret == vector<int>{0, 0});
    ret = s.searchRange(nums, 10);
    REQUIRE(ret == vector<int>{5, 6});
}
