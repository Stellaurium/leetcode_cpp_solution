//
// Created by stellaura on 28/08/24.
//

#include <catch2/catch_all.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    int trap(vector<int> &height) { return monotonicStackSolution(height); }

    template <typename ITER>
    int _calculateSum(ITER begin, ITER end) {
        int sum = 0;
        int last_highest = 0;
        for (auto it = begin; it != end; ++it) {
            auto h = *it;
            if (h > last_highest) {
                last_highest = h;
            } else {
                sum += last_highest - h;
            }
        }
        return sum;
    }
    // 首先找到这个height中最高的值
    // 将vector分成两半
    // 逻辑是 每次前进的时候 知道左侧最高柱子的大小
    // 右侧又一定有更高的
    // 所以积水高度为 左侧最高柱子的高度 - 自身高度
    int highestSolution(vector<int> &height) {
        if (height.empty())
            return 0;

        int highest = 0;
        int index = 0;
        for (int i = 0; i < height.size(); i++) {
            if (height[i] > highest) {
                highest = height[i];
                index = i;
            }
        }

        // 尾后位置
        int left_sum = _calculateSum(height.begin(), height.begin() + index + 1);
        int right_sum = _calculateSum(height.rbegin(), height.rend() - index);

        return left_sum + right_sum;
    }

    // 一个位置的能接到水的多少
    // 取决于两侧的柱子的高度的最小值
    // 所以与处理两侧的高度
    // 然后 min 即可
    int dynamicSolution(vector<int> &height) {
        int size = height.size();
        vector<int> forward_height(size, 0);
        vector<int> backward_height(size, 0);

        // 这个左右侧最小值是包括自己的
        // 如果两侧的最高值都不是自己 那么无所谓
        // 如果 有一册没有最高值
        // 那么 如果不包括自己 算出来的雨水是负数
        int current_highest = 0;
        for (int i = 0; i < size; i++) {
            if (height[i] > current_highest) {
                current_highest = height[i];
            }
            forward_height[i] = current_highest;
        }

        current_highest = 0;
        for (int i = size - 1; i >= 0; i--) {
            if (height[i] > current_highest) {
                current_highest = height[i];
            }
            backward_height[i] = current_highest;
        }

        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += min(forward_height[i], backward_height[i]) - height[i];
        }
        return sum;
    }

    // 跟上面拆成两个的思想差不多
    // 最后两个指针的相遇位置一定是最大值
    int doublePointerSolution(vector<int> &height) {
        int sum = 0;
        int left = 0, right = height.size() - 1;
        int left_max = height[left], right_max = height[right];

        // 左右的max同样还是包括自己
        // 因为希望 left 和 right 在最大值相遇
        // 所以 left 和m right 中小的那个移动
        // 因此我们一定能保证 left 和 right中 有一个是 当前看见过的 最大值
        // (即那个方向上的max)
        // 如果 left < right 那么 显然 right就是那个方向的最大值
        // i.e. 所有其他的看见过的值 < right == right_max
        // 因此 left位置上的leftmax 显然 小于 当前的 right，因此小于left位置的 rightmax
        // 所以 left 位置的 min 就是leftmax
        while (left != right) {
            if (height[left] < height[right]) {
                sum += left_max - height[left];
                left++;
                if (height[left] > left_max) {
                    left_max = height[left];
                }
            } else {
                sum += right_max - height[right];
                right--;
                if (height[right] > right_max) {
                    right_max = height[right];
                }
            }
        }
        return sum;
    }

    // 单调栈
    // 单调栈的作用就是 可以O(N)复杂度计算出 数组在某个位置上 某个方向上的最大值 or 最小值

    int monotonicStackSolution(vector<int> &height) {
        int size = height.size();
        // value, index
        stack<std::pair<int, int>> stack;

        // 该方法维护的不变量是 不管在什么时候 接水的数量都是正确的
        //
        // 想象从侧面观察这个方格
        // 只能看见所有没有被挡住的柱子
        // 即 单调栈中的元素
        // 在单纯入栈的时候 我们什么也不做
        // 因为此时 加入元素小于栈顶元素 并且两者index紧挨着 根本无法接水
        // 在入栈更大的元素的时候
        // 我们我们需要填入水 因为大概率已经形成凹槽了
        // 每次出栈需要观察左右两边的元素的值 (左边是他左侧第一个紧邻的大于其的值)
        // 刚刚push进入的是右侧第一个大于其的元素
        // 因此我们将这个元素的高度补足到 左右 的min
        // 然后再乘以宽度
        // 这个方法相当于是水平方向添加水
        // 第一个方法 (从最高点拆开) 相当于是竖直方向添加水
        int sum = 0;
        //        for (int i = 0; i < size; i++) {
        //            if (!stack.empty()) {
        //                if (stack.top().first <= height[i]) {
        //
        //                    while (!stack.empty() && stack.top().first <= height[i]) {
        //                        // 这个是一定会出栈的
        //                        auto current_height = stack.top();
        //                        stack.pop();
        //                        // 栈为空的时候 就说明不可能在接水了 直接跳过 push 当前元素进去
        //                        if (stack.empty()) {
        //                            break;
        //                        }
        //                        // 但是这个不一定出栈
        //                        auto prev_height = stack.top();
        //                        auto min_height = min(prev_height.first, height[i]);
        //                        sum += (min_height - current_height.first) * (i - prev_height.second - 1);
        //                    }
        //                    stack.emplace(height[i], i);
        //
        //                } else {
        //                    stack.emplace(height[i], i);
        //                }
        //            } else {
        //                stack.emplace(height[i], i);
        //            }
        //        }

        // 可以简化逻辑
        for (int i = 0; i < size; i++) {
            // 这个条件不成立 根本不会进入 while循环 直接push
            //            if (!stack.empty()) {
            // 如果条件不成立 根本不会进入 while循环 直接push
            //                if (stack.top().first <= height[i]) {

            while (!stack.empty() && stack.top().first <= height[i]) {
                // 这个是一定会出栈的
                auto current_height = stack.top();
                stack.pop();
                // 栈为空的时候 就说明不可能在接水了 直接跳过 push 当前元素进去
                if (stack.empty()) {
                    break;
                }
                // 但是这个不一定出栈
                auto prev_height = stack.top();
                auto min_height = min(prev_height.first, height[i]);
                sum += (min_height - current_height.first) * (i - prev_height.second - 1);
            }
            stack.emplace(height[i], i);

            //                } else {
            //                    stack.emplace(height[i], i);
            //                }
            //            } else {
            //                stack.emplace(height[i], i);
            //            }
        }
        return sum;
    }
};

TEST_CASE("Test the solution for trap") {
    Solution solution;
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    CHECK(solution.trap(height) == 6);

    vector<int> height2 = {4, 2, 0, 3, 2, 5};
    CHECK(solution.trap(height2) == 9);
}
