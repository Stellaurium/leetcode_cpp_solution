//
// Created by Stellaura on 2023/10/11.
//

#include "tools.h"
#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;

class Solution {
 public:
	int jump(vector<int> &nums) {
		return solution(nums);
	}

	int solution(vector<int> &nums) {
//		与55类似 还是O(n)
//		动态规划 到需要n步的只能是n-1过来的
//    而且肯定连成一片 单调非递减
		auto size = nums.size();
//		用来动态规划的数组甚至不需要
//		std::vector<int> required_time(size);
		auto count = 0;
//		当前的前线(类似BFS)
		int begin = 0;
		int end = 0;
		int max_reachable_index = 0;
//		在每一个区间内搜索最大的可能性
//    然后更新区间
		while (end < size - 1) {
			for (int i = begin; i <= end; i++) {
				max_reachable_index = std::max(max_reachable_index, i + nums[i]);
			}
			begin = end + 1;
			end = max_reachable_index;

			count++;
		}
		return count;
	}
};

int main() {
	auto solution = Solution();
	auto v = std::vector<int>{2,3,0,1,4};
	auto max_value = solution.jump(v);
	std::cout << max_value << std::endl;
	return 0;
}
