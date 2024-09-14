//
// Created by stellaura on 14/09/24.
//
#include <algorithm>
#include <catch2/catch_all.hpp>
#include <map>
#include <set>
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
        std::map<std::set<int>, int64_t> memory;
        for (int i = 1; i <= 40; i++) {
            available_array[i] = true;
        }
        vector<set<int>> all_need(11, set<int>());
        for (int i = hats.size() - 1; i >= 0; i--) {
            set_union(all_need[i + 1].begin(), all_need[i + 1].end(), hats[i].begin(), hats[i].end(),
                      std::inserter(all_need[i], all_need[i].begin()));
        }
        return backtrack_(hats, 0, set<int>(), memory, all_need);
    }

    int64_t backtrack_(vector<vector<int>> &hats, int index, set<int> selected,
                       std::map<std::set<int>, int64_t> &memory, vector<set<int>> &all_need) {
        set<int> current_possible_hat;
        set_difference(all_need[index].begin(), all_need[index].end(), selected.begin(), selected.end(),
                       std::inserter(current_possible_hat, current_possible_hat.begin()));
        if (memory.contains(current_possible_hat)) {
            return memory[current_possible_hat];
        }

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
            auto new_selected = set<int>(selected);
            new_selected.insert(e);
            dfs_count += backtrack_(hats, index + 1, new_selected, memory, all_need);
            dfs_count %= kMOD;
            available_array[e] = 1;
        }

        memory[current_possible_hat] = dfs_count;
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
