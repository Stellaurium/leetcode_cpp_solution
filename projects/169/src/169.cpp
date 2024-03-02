#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <ctime>
using std::vector;

//majority-element

class Solution {
 public:
  int majorityElement(vector<int> &nums) {
	return solution5(nums);
  }
 private:
  int solution1(vector<int> &nums) {
//	map
// unordered_map 远远快于map
	auto m = std::unordered_map<int, int>();
//	c++ map 拿出来就默认初始化了
	for (auto e : nums) {
	  ++m[e];
	}
	int max_number;
	int max = -1;
	for (auto p : m) {
	  if (p.second > max) {
		max = p.second;
		max_number = p.first;
	  }
	}
	return max_number;
  }
  int solution2(vector<int> &nums) {
//	sort
	std::sort(nums.begin(), nums.end());
	return nums[nums.size() / 2];

  }



  int solution4(vector<int> &nums) {
//	random
	std::random_device rd;
	auto generator = std::mt19937_64(rd());
	std::uniform_int_distribution<int> distribution(0, nums.size() - 1);
	int index;
	while (true) {
	  index = distribution(generator);
	  if (check_majority(nums, nums[index])) {
		return nums[index];
	  }
	}

  }
  bool check_majority(std::vector<int> v, int num) {
	int count = 0;
	for (auto e : v) {
	  if (e == num) {
		++count;
	  }
	}
	if (count > v.size() / 2) {
	  return true;
	} else {
	  return false;
	}
  }

  int solution5(vector<int> &nums) {
//	dynamic program
	int health = 1;
	int hero = nums[0];
	for (int index = 1; index < nums.size(); ++index) {
	  if (nums[index] == hero) {
		++health;
	  } else {
		--health;
	  }
	  if (health == 0) {
		++index;
		hero = nums[index];
		health = 1;
	  }
	}
	return hero;
  }

};

int main() {
  auto solution = Solution();
  auto v = std::vector<int>{3, 2, 3};
  std::cout << solution.majorityElement(v) << std::endl;

  return 0;
}