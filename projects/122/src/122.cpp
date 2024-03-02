//
// Created by Stellaura on 2023/9/25.
//
#include "tools.h"
#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
  public:
    int maxProfit(vector<int> &prices) { return solution1(prices); }

  private:
    int solution1(vector<int> &prices) {
        // 动态规划
        int max_profit = 0;
        int temp;
        for (int i = 1; i != prices.size(); ++i) {
            temp = prices[i] - prices[i - 1];
            if (temp > 0) {
                max_profit += temp;
            }
        }
        return max_profit;
    }
};

int main() {
    auto solution = Solution();
    auto v = std::vector<int>{7, 1, 5, 3, 6, 4};
    auto max_value = solution.maxProfit(v);
    std::cout << max_value << std::endl;
    return 0;
}