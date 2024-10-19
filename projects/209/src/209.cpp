//
// Created by stellaura on 19/10/24.
//
#include <catch2/catch_all.hpp>
#include <limits>
#include <vector>

using namespace std;

class Solution {
  public:
    int minSubArrayLen(int target, vector<int> &nums) {
        int begin = 0;
        int end = -1;
        int sum = 0;
        int min_len = std::numeric_limits<int>::max();
        int size = nums.size();
        while (true) {
            if (sum < target) {
                end++;
                if (end == size) {
                    break;
                }
                sum += nums[end];
            } else {
                // update len
                if (min_len > end - begin + 1) {
                    min_len = end - begin + 1;
                }
                sum -= nums[begin];
                begin++;
            }
        }

        if (min_len == std::numeric_limits<int>::max()) {
            return 0;
        }
        return min_len;
    }
};

TEST_CASE("Test Solution") {
    Solution s;
    std::vector<int> v;

    v = std::vector{2, 3, 1, 2, 4, 3};
    REQUIRE(s.minSubArrayLen(7, v) == 2);

    v = std::vector{1, 1, 1, 1, 1, 1, 1, 1};
    REQUIRE(s.minSubArrayLen(11, v) == 0);
}
