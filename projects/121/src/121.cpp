//
// Created by Stellaura on 2023/9/25.
//
#include "tools.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <ctime>
using std::vector;

class Solution {
 public:
  int maxProfit(vector<int> &prices) {
	int min = prices[0];
	int max_profit = 0;
	for (int i = 1; i != prices.size(); ++i) {
	  if(prices[i] - min > max_profit){
		max_profit = prices[i] - min;
	  }
	  else if(prices[i] < min){
		min = prices[i];
	  }
	}
	return max_profit;
  }
};

int main() {
  auto solution = Solution();
  auto v = std::vector<int>{7,1,5,3,6,4};
  auto max_value = solution.maxProfit(v);
  std::cout << max_value << std::endl;
  return 0;
}