#include "tools.h"
#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;

class Solution {
 public:

	bool canJump(vector<int> &nums) {
		return solution3(nums);
	}

	bool solution1(vector<int> &nums) {
//		O(sum(nums) + n)复杂度

//从后向前
		int size = nums.size();
		bool flags[size];
		for (int i = 0; i != size; ++i) {
			flags[i] = false;
		}
		flags[size - 1] = true;
		for (int i = size - 2; i >= 0; --i) {
			int max_range = std::min(i + nums[i], size - 1);
			for (int j = i + 1; j <= max_range; ++j) {
				if (flags[j]) {
					flags[i] = true;
				}
			}

		}
		return flags[0];
	}

	bool solution2(vector<int> &nums) {
//		O(sum(nums) + n)复杂度

//		从前向后
		int size = nums.size();
		bool flags[size];
		for (int i = 0; i != size; ++i) {
			flags[i] = false;
		}
		flags[0] = true;
		for (int i = 0; i != size; i++) {
			if (flags[i]) {
				for (int j = 1; j <= nums[i] && i + j < size; j++) {
					flags[i + j] = true;
				}
			}
		}
		return flags[size - 1];
	}

	bool solution3(vector<int> &nums) {
//		O(n)算法
//	原理： 中间不可能出现空洞(如果能过去 必定能覆盖中间的所有)
//	所以只需要跟新一个能到达的最大值
//  如果现在的下标大于可到达的最大长度 判定false
		int size = nums.size();
		int max_reachable_index = 0;
		for (int i = 0; i != size; ++i) {
			if (i > max_reachable_index) {
				return false;
			} else {
				max_reachable_index = std::max(max_reachable_index, i + nums[i]);

			}
		}
		return true;
	}

};

int main() {
	auto solution = Solution();
	auto v = std::vector<int>{3,2,1,0,4};
	auto max_value = solution.canJump(v);
	std::cout << max_value << std::endl;
	return 0;
}