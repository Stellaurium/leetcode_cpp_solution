//
// Created by stellaura on 31/08/24.
//
#include <catch2/catch_all.hpp>
#include <deque>
#include <functional>
#include <vector>

using namespace std;

// 天津大学 预推免第四题
// 知道应该使用 单调队列 但是差一点点
// 最后五分钟想出来了 都晚了

// min-queue 使用 less
void pushMonotoneQueue(deque<pair<int, int>> &q, const std::function<bool(int, int)> &comp, int num, int index) {
    while (!q.empty() && comp(q.back().first, num)) {
        q.pop_back();
    }
    q.emplace_back(num, index);
}

// 电调队列可以用 O(1) 的时间 获取一个区间内的极值
class Solution {
  public:
    int longestSubarray(vector<int> &nums, int limit) {
        deque<pair<int, int>> min_q;
        deque<pair<int, int>> max_q;
        int begin = 0;
        int end = 0;
        int max_length = 0;

        for (end = 0; end < nums.size(); end++) {
            pushMonotoneQueue(min_q, greater_equal<int>(), nums[end], end);
            pushMonotoneQueue(max_q, less_equal<int>(), nums[end], end);

            // 该区间肯定不行了 同时 end不管怎么++也不可能是正确答案了
            // 因此剪枝end后面的
            // 让begin++
            // 因为现在是不满足的 但是刚才满足
            // 因此添加了 当前元素后 一定改变了 min 或者 max
            // 我们可以比较 min_q.front().second 和 max_q.front().second
            // 大的那个一定就是刚才刚插入的元素
            // 其他另一个队列中的所有元素都一定是当前元素的index小的
            // 因此只需要不断pop front 另一个队列
            // 直到刚好不满足那个极值的后面一个元素
            int last_extremum_index = 0;
            if (max_q.front().first - min_q.front().first > limit) {

                if (min_q.front().second < max_q.front().second) {
                    // pop min
                    // 需要确保不会弹空
                    // 但是因为不管插入什么 这个元素一定会在两个队列的底部
                    // 两者的插值必定是0 满足limit
                    // 所以队列永远不会空
                    // while (!min_q.empty() && max_q.front().first - min_q.front().first > limit){
                    while (max_q.front().first - min_q.front().first > limit) {
                        last_extremum_index = min_q.front().second;
                        min_q.pop_front();
                    }
                } else {
                    // pop max
                    while (max_q.front().first - min_q.front().first > limit) {
                        last_extremum_index = max_q.front().second;
                        max_q.pop_front();
                    }
                }
                begin = last_extremum_index + 1;
            }

            if (end - begin + 1 > max_length) {
                max_length = end - begin + 1;
            }
        }
        return max_length;
    }
};

TEST_CASE("test longestSubarray") {
    Solution s;

    vector<int> nums{10, 1, 2, 4, 7, 2};
    int result = s.longestSubarray(nums, 5);
    REQUIRE(result == 4);

    vector<int> nums2{4, 2, 2, 2, 4, 4, 2, 2};
    int result2 = s.longestSubarray(nums2, 0);
    REQUIRE(result2 == 3);

    vector<int> nums3{4, 2, 100, 2, 4, 4, 2, 2, 2};
    int result3 = s.longestSubarray(nums3, 0);
    REQUIRE(result3 == 3);
}
