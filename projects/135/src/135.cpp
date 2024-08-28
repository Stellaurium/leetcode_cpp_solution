#include <catch2/catch_all.hpp>
#include <iostream>
#include <numeric> // 用于 std::accumulate
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    int candy(vector<int> &ratings) { return candySolution(ratings); }

    int candySolution(vector<int> &ratings) {
        int n = ratings.size();
        if (n == 0)
            return 0;

        int total_candies = 0;
        vector<int> subarray;

        for (int i = 0; i < n; ++i) {
            subarray.push_back(ratings[i]);

            if (i == n - 1 || ratings[i] == ratings[i + 1]) {
                total_candies += _candySolutionFast2(subarray);
                subarray.clear();
            }
        }

        return total_candies;
    }

    // 自己想出来的单方向算法
    // 使用刚刚学到的差分和求和的方式
    // 差分可以使得一段区间同时 +1 的时间复杂的是 O(1) (额外的与处理)
    // 我们只想要计算出来这个答案的差分结果
    // diff[0] 初始为 1 (a_0 == diff[0])
    // 然后考虑后面上升 下降 相当的问题
    // 首先相等
    // 如果两个相邻的元素相等
    // 则两个元素之间没有任何依赖的关系
    // 我们可以直接将数组切成两个
    // 然后分别求解
    // 因此我们只需要考虑 上升或者下降即可
    // 如果上升 显然 +1 是最合理的
    // 如果是上升转为下降 显然 直接重置为 1是最合理的
    // 如果是下降接着下降 显然让下一个为1,同时让这一个下降区间内关联的元素+1
    // 但是 如果这个区间的开头不能+1 即 diff已经为 -1 了，没有继续提升的空间了
    // 发现 让这个下降区间的第一个的前一个(rating的局部最大值) 跟着+1 即可
    // 不需要改变上一个上升下降区间
    // 因此这个问题 可以O(n) 解决
    // 只需要记住当前的情况即可
    int _candySolution(vector<int> &ratings) {
        int n = ratings.size();
        if (n == 0)
            return 0;

        vector<int> diff(n, 0); // 差分数组
        int current_candy = 1;
        diff[0] = 1;
        // 记录上一个i 使得 rating[i] < rating[i-1] 的索引
        int last_decrease_index = 0;
        bool is_increasing = true;

        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                is_increasing = true;
                diff[i] = 1;
                current_candy += 1;
            } else if (ratings[i] < ratings[i - 1]) {
                if (is_increasing) {
                    is_increasing = false;
                    last_decrease_index = i;
                }
                // 直接降为1
                if (current_candy > 1) {
                    diff[i] = -current_candy + 1;
                    current_candy = 1;
                } else {
                    diff[i] = -1;

                    // 已经没办法提升了
                    // 这个甚至偷偷跳过了 开头是下降序列的问题
                    // 如果开头就下降 那么会让 diff[last_decrease_index] + 1
                    // 即 a_0 + 1
                    // 但是 a_0 >0 != -1
                    // 所以一定能加到这个地方
                    if (diff[last_decrease_index] == -1) {
                        // 让这一部分下降的起始点的diff + 1
                        diff[last_decrease_index - 1] += 1;
                    } else {
                        diff[last_decrease_index] += 1;
                    }
                    // current_candy = 1; // 这个东西已经是1了
                }
            }
        }

        vector<int> candy(n, 0);
        candy[0] = diff[0];
        for (int i = 1; i < n; i++) {
            candy[i] = candy[i - 1] + diff[i];
        }
        return accumulate(candy.begin(), candy.end(), 0);
    }

    // 上面的方法的优化方法
    // 根本不需要diff
    // O(1) 空间
    // 这个方法是每次加一段上升或者下降
    int _candySolutionFast(vector<int> &ratings) {
        int sum = 0;
        int last_increasing_count = 0;
        int count = 1; // 一旦有至少就是两个
        bool is_increasing = true;
        bool is_first_calc_sum = true;

        // 可以看出来不管一开始是上升还是下降，第一个计算的都是sum都是increasing的
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) {
                if (!is_increasing) {
                    is_increasing = true;
                    if (count > last_increasing_count) {
                        sum -= last_increasing_count;
                        sum += count * (count + 1) / 2;
                    } else {
                        sum += count * (count - 1) / 2;
                    }
                    count = 1;
                }
                count++;
            } else {
                if (is_increasing) {
                    is_increasing = false;

                    // 排除上一个已经计算过的 上升序列的开头的1
                    sum += count * (count + 1) / 2 - 1;
                    if (is_first_calc_sum) {
                        sum += 1;
                        is_first_calc_sum = false;
                    }
                    last_increasing_count = count;
                    // 开始数下降的个数了
                    // 这个以及前一个 现在以及两个了
                    // 但是下面 ++ 这里设置为 1
                    count = 1;
                }
                count++;
            }
        }

        if (is_increasing) {
            sum += count * (count + 1) / 2 - 1;
            if (is_first_calc_sum) {
                sum += 1;
            }
        } else {
            if (count > last_increasing_count) {
                sum -= last_increasing_count;
                sum += count * (count + 1) / 2;
            } else {
                sum += count * (count - 1) / 2;
            }
        }

        return sum;
    }

    // 这个方法是每次加一个
    int _candySolutionFast2(vector<int> &ratings) {
        // 算上第一个数字
        int sum = 1;
        int last_increasing_count = 0;
        int count = 1; // 一旦有至少就是两个
        bool is_increasing = true;
        bool is_first_calc_sum = true;

        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) {
                if(!is_increasing){
                    is_increasing = true;
                    count = 1;
                }
                count++;
                sum += count;
                is_increasing = true;
            } else {
                if (is_increasing) {
                    is_increasing = false;
                    last_increasing_count = count;
                    // 因为不算上一次的上升的结尾了
                    count = 0;
                }
                count ++;
                if(count >= last_increasing_count){
                    sum += count + 1;
                }
                else{
                    sum += count;
                }
            }
        }
        return sum;
    }

    // 双方向扫描
    // 显然我们现在已经知道了这个题目的上升和下降不会影响很远
    // 只需要维持 O(1) 的记忆
    // 同时局部最小值 分到的糖果一定是1
    // 因此我们可以从局部最小值出发
    // 向两端前进 逐步 +1
    // 如果有两个局部最小值之间有冲突
    // 就取max
    // 该算法空间复杂度 O(n)
    int doubleScan(vector<int> &ratings) {
        int n = ratings.size();
        // 每个人至少一个 所以都初始化为1 为最小值 一定会被max掉
        // 同时不需要考虑上升 或 下降时 第一个需要初始化为1
        auto left_vector = vector<int>(n, 1);
        left_vector[0] = 1;
        auto right_vector = vector<int>(n, 1);
        right_vector[n - 1] = 1;

        for (int i = 1; i < n; i++) {
            if (ratings[i - 1] < ratings[i]) {
                left_vector[i] = left_vector[i - 1] + 1;
            }
        }

        for (int i = n - 1; i >= 1; i--) {
            if (ratings[i - 1] > ratings[i]) {
                right_vector[i - 1] = right_vector[i] + 1;
            }
        }

        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += max(left_vector[i], right_vector[i]);
        }
        return sum;
    }
};

TEST_CASE() {
    Solution s;
    vector<int> ratings1 = {1, 0, 2};
    CHECK(s.candy(ratings1) == 5);

    vector<int> ratings2 = {1, 2, 2};
    CHECK(s.candy(ratings2) == 4);

    vector<int> ratings3 = {1, 2, 87, 87, 87, 2, 1};
    CHECK(s.candy(ratings3) == 13);

    vector<int> ratings4 = {1, 6, 10, 8, 7, 3, 2};
    CHECK(s.candy(ratings4) == 18);

    vector<int> ratings5 = {0,1,2,5,3,2,7};
    CHECK(s.candy(ratings5) == 15);

}
