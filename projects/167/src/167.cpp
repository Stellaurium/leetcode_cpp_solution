//
// Created by stellaura on 03/09/24.
//
#include <catch2/catch_all.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        int begin = 0;
        int end = numbers.size() - 1;
        while (begin < end) {
            if (numbers[begin] + numbers[end] == target) {
                return {begin + 1, end + 1};
            }
            if (numbers[begin] + numbers[end] < target) {
                begin++;
            } else {
                end--;
            }
        }
        return {};
    }
};

TEST_CASE("Test Solution"){
    Solution s;
    vector<int> numbers = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = s.twoSum(numbers, target);
    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 2);


}