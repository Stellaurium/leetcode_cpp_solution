#include "tools.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <ctime>
using std::vector;



//class
class Solution {
 public:
  void rotate(vector<int> &nums, int k) {
	int size = nums.size();
//	数论 判断是否互质
	int gcd_number = gcd(k, size);
	for (int i = 0; i != gcd_number; ++i) {
	  int index = i;
	  int last_value = nums[mod(index - k, size)];
	  int current_value;
	  for (int j = 0; j != size / gcd_number; ++j) {
		current_value = nums[index];
		nums[index] = last_value;
		last_value = current_value;
		index = mod(index + k, size);
	  }
	}
  }

};



int main() {
  auto solution = Solution();
  auto v = std::vector<int>{1,2,3,4,5,6,7};
  solution.rotate(v, 3);
  print_vector(v);
  return 0;
}