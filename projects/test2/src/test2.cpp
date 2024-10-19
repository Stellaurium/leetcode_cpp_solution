//
// Created by stellaura on 15/09/24.
//
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

// 保存每个帽子的占用情况
int available_array[41];

constexpr int64_t kMOD = 1000000007;

class Solution {
  public:
    int numberWays(vector<vector<int>> &hats) { return backtrack(hats); }

  private:
    int backtrack(vector<vector<int>> &hats) {
        // 使用两层 map 进行优化
        map<int, map<set<int>, int64_t>> memory;
        for (int i = 1; i <= 40; i++) {
            available_array[i] = true;
        }
        vector<set<int>> all_need(11);
        for (int i = hats.size() - 1; i >= 0; i--) {
            all_need[i].insert(hats[i].begin(), hats[i].end());
            if (i < hats.size() - 1) {
                for (const auto &item : all_need[i + 1]) {
                    all_need[i].insert(item);
                }
            }
        }
        return backtrack_(hats, 0, set<int>(), memory, all_need);
    }

    int64_t backtrack_(vector<vector<int>> &hats, int index, set<int> selected,
                       map<int, map<set<int>, int64_t>> &memory, vector<set<int>> &all_need) {
        if (memory[index].find(selected) != memory[index].end()) {
            return memory[index][selected];
        }

        set<int> current_possible_hat;
        for (const auto &hat : all_need[index]) {
            if (selected.find(hat) == selected.end()) {
                current_possible_hat.insert(hat);
            }
        }

        if (index == hats.size()) {
            return 1;
        }

        int64_t dfs_count = 0;
        const auto &hat = hats[index];
        for (auto e : hat) {
            if (available_array[e] == 0) {
                continue;
            }
            available_array[e] = 0;
            auto new_selected = selected;
            new_selected.insert(e);
            dfs_count += backtrack_(hats, index + 1, new_selected, memory, all_need);
            dfs_count %= kMOD;
            available_array[e] = 1;
        }

        memory[index][selected] = dfs_count;
        return dfs_count;
    }
};


int main() {
    Solution solution;
    vector<vector<int>> hats = {
        {2,12,18,20,24,26,30},
        {1,2,4,5,8,9,10,11,13,15,16,17,19,20,21,22,24,26,28,29},
        {9,10,13,14,18,27},
        {1,2,3,7,9,15,16,18,28},
        {2,3,5,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,26,27,30},
        {2,11,14,25},
        {2,3,5,6,7,8,9,11,13,16,17,18,19,20,21,22,24,26,27,28,29,30}
    };

    int result = solution.numberWays(hats);
    cout << "Number of ways: " << result << endl;

    return 0;
}
