#include <catch2/catch_all.hpp>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode *reverseBetween(ListNode *head, int left, int right) {
        ListNode *node0 = new ListNode(0);
        ListNode *current = node0;
        node0->next = head;
        // reverse两侧的节点
        ListNode *begin_node, *end_node;
        ListNode *new_list = nullptr;
        ListNode *prev_node, *next_node;

        int index = 0;
        while (index != left - 1) {
            index++;
            current = current->next;
        }
        // 到了左端点的前面
        begin_node = current;
        // 再走一步到起始
        index++;
        current = current->next;
        end_node = current;

        while (index <= right) {
            next_node = current->next;
            current->next = new_list;
            new_list = current;
            current = next_node;
            index++;
        }
        end_node->next = current;
        begin_node->next = new_list;

        return node0->next;
    }
};

TEST_CASE() {
    Solution s{};
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    auto ret = s.reverseBetween(head, 2, 4);
    // 1 4 3 2 5
    REQUIRE(ret->val == 1);
    ret = ret->next;
    REQUIRE(ret->val == 4);
    ret = ret->next;
    REQUIRE(ret->val == 3);
    ret = ret->next;
    REQUIRE(ret->val == 2);
    ret = ret->next;
    REQUIRE(ret->val == 5);

    ret = s.reverseBetween(head, 1, 4);
    // 2 3 4 1 5
    REQUIRE(ret->val == 2);
    ret = ret->next;
    REQUIRE(ret->val == 3);
    ret = ret->next;
    REQUIRE(ret->val == 4);
    ret = ret->next;
    REQUIRE(ret->val == 1);
    ret = ret->next;
    REQUIRE(ret->val == 5);
    
}