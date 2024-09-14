//
// Created by stellaura on 03/09/24.
//
#include <vector>
#include <catch2/catch_all.hpp>

using namespace std;

class Solution {
  public:
    int maxArea(vector<int>& height) {
        int begin = 0;
        int end = height.size() - 1;
        int max_area = 0;

        while(begin < end){
            auto area = (end - begin) * min(height[begin], height[end]);
            max_area = max(max_area, area);
            if(height[begin] < height[end]){
                begin++;
            }
            else{
                end--;
            }
        }
        return max_area;
    }
};

TEST_CASE("Test the solution for maxArea") {
    Solution solution;
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    REQUIRE(solution.maxArea(height) == 49);
}