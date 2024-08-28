
#include <catch2/catch_all.hpp>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {
  public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) { return plusAndMinus(gas, cost); }
    bool bruceForceFlag(vector<int> &gas, vector<int> &cost, int start) {
        int size = gas.size();
        int remain_gas = gas[start];
        for (int j = 0; j < size; j++) {
            remain_gas = remain_gas - cost[(start + j) % size];
            if (remain_gas < 0) {
                return false;
            }
            remain_gas += gas[(start + j + 1) % size];
        }
        remain_gas -= cost[start];
        return remain_gas >= 0;
    }

    [[maybe_unused]] int bruceForce(vector<int> &gas, vector<int> &cost) {
        bool flag = true;
        int size = gas.size();
        for (int i = 0; i < size; i++) {
            if (bruceForceFlag(gas, cost, i)) {
                return i;
            }
        }
        return -1;
    }

    [[maybe_unused]] int bruceForceGPT(vector<int> &gas, vector<int> &cost) {
        int size = gas.size();
        for (int i = 0; i < size; i++) {
            int remain_gas = 0;
            bool can_complete = true;
            for (int j = 0; j < size; j++) {
                remain_gas += gas[(i + j) % size] - cost[(i + j) % size];
                if (remain_gas < 0) {
                    can_complete = false;
                    break;
                }
            }
            if (can_complete) {
                return i;
            }
        }
        return -1;
    }
    [[maybe_unused]] int prefixSum(vector<int> &gas, vector<int> &cost) {
        int size = gas.size();
        auto A = new int[size + 1];
        A[0] = 0;
        for (int i = 1; i < size + 1; i++) {
            A[i] = A[i - 1] + gas[i - 1] - cost[i - 1];
        }

        bool flag = true;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                flag = true;
                int sum = 0;
                if (i + j >= size) {
                    sum = A[i + j + 1 - size] - A[i] + A[size];
                } else {
                    sum = A[i + j + 1] - A[i];
                }
                if (sum < 0) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return i;
            }
        }
        return -1;
    }

    // 这个想法相当新奇
    // 首先创建那个两个数组作差的数组
    // 由于需要频繁删减 使用list
    // 现在考虑当前位置是 正数的情况
    // 如果 后面是正数 那么如果后面那个点是答案 则前面这个正数的点一定可行
    // 矛盾 所以 可以将两个正数的点合并成一个
    // 如果 后面是负数 那么如果两者的和大于 0 ，则可以合并成一个正的节点 (不可能从负数开始)
    // 如果 后面是负数 那么如果两者的和小于 0 ，则根本不可能从这两个点开始
    // 所以我们把这两个点合并成一个负数
    // 由于上面都是从正数开始的
    // 因此我们循环观察这个list 找到正数就执行这个操作
    // 如果最后可行的话 一定可以剩下一个正数
    // 如果不可行 一定剩下负数
    [[maybe_unused]] int plusAndMinus(vector<int> &gas, vector<int> &cost) {
        list<std::pair<int, int>> A;
        int size = gas.size();
        for (int i = 0; i < size; i++) {
            A.emplace_back(gas[i] - cost[i], i);
        }

        auto it = A.begin();
        while (A.size() > 1) {
            auto temp_it = it;
            temp_it++;
            if (temp_it == A.end()) {
                temp_it = A.begin();
            }
            if ((*it).first >= 0) {

                (*it).first += (*temp_it).first;
                A.erase(temp_it);
            } else {
                if ((*temp_it).first <= 0) {
                    (*it).first += (*temp_it).first;
                    A.erase(temp_it);
                } else {
                    it++;
                    if (it == A.end()) {
                        it = A.begin();
                    }
                }
            }
        }

        // parse last result
        auto last_element = *(A.begin());
        if (last_element.first >= 0) {
            return last_element.second;
        } else {
            return -1;
        }
    }
};

TEST_CASE() {
    Solution s;
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};
    REQUIRE(s.canCompleteCircuit(gas, cost) == 3);

    gas = {2, 3, 4};
    cost = {3, 4, 3};
    REQUIRE(s.canCompleteCircuit(gas, cost) == -1);
}
