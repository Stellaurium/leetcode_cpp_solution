//
// Created by Stellaura on 2023/10/11.
//

#include "tools.h"
#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
  public:
    int hIndex(vector<int> &citations) { return solution1(citations); }

    int solution1(vector<int> &citations) {
        std::sort(citations.begin(), citations.end(), std::greater<int>());
        print_vector(citations);
        int i = 0;
        //		从0计数
        int size = citations.size();
        while (i < size and i < citations[i]) {
            i++;
        }
        return i;
    }
};

int main() {
    auto solution = Solution();
    auto v = std::vector<int>{1};
    auto answer = solution.hIndex(v);
    std::cout << answer << std::endl;
    return 0;
}
