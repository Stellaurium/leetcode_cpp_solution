//
// Created by stellaura on 14/09/24.
//
#include <catch2/catch_all.hpp>
#include <vector>
using namespace std;

// 保存每个帽子的占用情况
int available_array[41];
// 保存第i个人选择他喜欢的第几个选项

int64_t count;

constexpr int64_t kMOD = 1000000007;

class Solution {
  public:
    int numberWays(vector<vector<int>> &hats) { return backtrack(hats); }

  private:
    // 回溯超时
    int backtrack(vector<vector<int>> &hats) {
        for (int i = 1; i <= 40; i++) {
            available_array[i] = true;
        }
        return backtrack_(hats, 0);
    }

    int64_t backtrack_(vector<vector<int>> &hats, int index) {
        if (index == hats.size()) {
            return 1;
        }

        int64_t dfs_count = 0;
        auto &hat = hats[index];
        for (auto e : hat) {
            if (available_array[e] == 0) {
                continue;
            }
            available_array[e] = 0;
            dfs_count += backtrack_(hats, index + 1);
            dfs_count %= kMOD;
            available_array[e] = 1;
        }

        return dfs_count;
    }
};

TEST_CASE("Test Solution", "[numberWays]") {
    Solution s;
    // [[3,4],[4,5],[5]]
    vector<vector<int>> hats = {{3, 4}, {4, 5}, {5}};
    REQUIRE(s.numberWays(hats) == 1);

    //[[3,5,1],[3,5]]
    hats = {{3, 5, 1}, {3, 5}};
    REQUIRE(s.numberWays(hats) == 4);

    //[[1,2,3,4],[1,2,3,4],[1,2,3,4],[1,2,3,4]]
    // 输出：24
    hats = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
    REQUIRE(s.numberWays(hats) == 24);

    //[[1,2,3],[2,3,5,6],[1,3,7,9],[1,8,9],[2,5,7]]
    hats = {{1, 2, 3}, {2, 3, 5, 6}, {1, 3, 7, 9}, {1, 8, 9}, {2, 5, 7}};
    REQUIRE(s.numberWays(hats) == 111);
}