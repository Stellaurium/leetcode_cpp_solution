//
// Created by stellaura on 27/07/24.
//
#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include <algorithm>
#include <climits>
#include <map>
#include <unordered_map>
#include <vector>

class Solution {
  private:
    std::unordered_map<int, int> m;
    int *a;

    int _calc_coin_count_map(std::vector<int> &coins, int amount) {
        if (amount < 0) {
            return std::numeric_limits<int>::max();
        }
        if (amount == 0) {
            return 0;
        }
        if (m.contains(amount)) {
            return m[amount];
        } else {
            int ret_value = std::numeric_limits<int>::max();
            for (auto coin_value : coins) {
                int temp = _calc_coin_count_map(coins, amount - coin_value);
                // 需要判断以下是不是可以完成任务 不能直接+1 会溢出
                if (temp != std::numeric_limits<int>::max() && ret_value > temp + 1) {
                    ret_value = temp + 1;
                }
            }
            m[amount] = ret_value;
            return ret_value;
        }
    }

    int _calc_coin_count_array(std::vector<int> &coins, int amount) {
        if (amount < 0) {
            return std::numeric_limits<int>::max();
        }
        if (amount == 0) {
            return 0;
        }
        if (a[amount] != 0) {
            return a[amount];
        } else {
            int ret_value = std::numeric_limits<int>::max();
            for (auto coin_value : coins) {
                int temp = _calc_coin_count_array(coins, amount - coin_value);
                if (temp != std::numeric_limits<int>::max() && ret_value > temp + 1) {
                    ret_value = temp + 1;
                }
            }
            a[amount] = ret_value;
            return ret_value;
        }
    }

    // very slow
    // map 1000ms
    // unordered_map 330ms
    int _coinChange_1(std::vector<int> &coins, int amount) {
        std::sort(coins.begin(), coins.end(), std::greater<int>{});
        auto ret = _calc_coin_count_map(coins, amount);
        if (ret == std::numeric_limits<int>::max()) {
            return -1;
        } else {
            return ret;
        }
    }

    // fast  30ms
    int _coinChange_2(std::vector<int> &coins, int amount) {
        std::sort(coins.begin(), coins.end(), std::greater<int>{});
        a = new int[amount + 1];
        std::fill(a, a + amount + 1, 0);

        std::sort(coins.begin(), coins.end(), std::greater<int>{});
        auto ret = _calc_coin_count_array(coins, amount);

        delete[] a; // Don't forget to free the memory

        if (ret == std::numeric_limits<int>::max()) {
            return -1;
        } else {
            return ret;
        }
    }

    // 所以不要用map
    // fast 20ms
    int _coinChange_3(std::vector<int> &coins, int amount) {
        auto A = new int[amount + 1];
        memset(A, 0, sizeof(int) * (amount + 1));
        for (int i = 1; i <= amount; i++) {
            int ret_value = std::numeric_limits<int>::max();
            for (auto coin_value : coins) {
                if (i - coin_value < 0) {
                    continue;
                }
                if (A[i - coin_value] == -1) {
                    continue;
                }
                if (ret_value > A[i - coin_value] + 1) {
                    ret_value = A[i - coin_value] + 1;
                }
            }
            if (ret_value == std::numeric_limits<int>::max()) {
                A[i] = -1;
            } else {
                A[i] = ret_value;
            }
        }
        auto ret = A[amount];
        delete[] A;
        return ret;
    }

  public:
    int coinChange(std::vector<int> &coins, int amount) { return _coinChange_2(coins, amount); }
};

TEST_CASE() {
    Solution s{};
    SECTION("coins = [1,2,5], amount = 11") {
        auto v = std::vector{1, 2, 5};
        auto ret = s.coinChange(v, 11);
        REQUIRE(ret == 3);
    }
}
