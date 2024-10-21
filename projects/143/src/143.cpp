//
// Created by stellaura on 21/10/24.
//
#include <catch2/catch_all.hpp>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
    void reorderList(ListNode *head) {
        auto slow = head;
        auto fast = head;
        int count = 0;
        // 需要中间偏左
        // 此时 slow 是第一个链表的结尾
        while (fast->next) {
            if (count % 2) {
                slow = slow->next;
            }
            fast = fast->next;
            count++;
        }

        // 处理只有一个节点的情况
        if (slow == fast)
            return;

        // 让两组链表都之向中间
        ListNode *prev = nullptr;
        auto current = slow;
        auto next = current->next;
        while (next) {
            prev = current;
            current = next;
            next = next->next;

            current->next = prev;
        }

        // 断开链表
        slow->next->next = nullptr;
        slow->next = nullptr;
        auto node0 = new ListNode(0);
        auto list1 = head;
        auto list2 = current;
        auto next_node = list1;
        current = node0;
        count = 0;
        while (next_node) {
            current->next = next_node;
            current = current->next;
            // 注意顺序是反的
            if (count % 2) {
                next_node = list1;
                list2 = list2->next;
            } else {
                next_node = list2;
                list1 = list1->next;
            }
            count++;
        }
        delete node0;
    }
};

TEST_CASE() {
    Solution s;

    SECTION("5 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);

        s.reorderList(head);
        REQUIRE(head->val == 1);
        head = head->next;
        REQUIRE(head->val == 5);
        head = head->next;
        REQUIRE(head->val == 2);
        head = head->next;
        REQUIRE(head->val == 4);
        head = head->next;
        REQUIRE(head->val == 3);
    }

    SECTION("4 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);

        s.reorderList(head);
        REQUIRE(head->val == 1);
        head = head->next;
        REQUIRE(head->val == 4);
        head = head->next;
        REQUIRE(head->val == 2);
        head = head->next;
        REQUIRE(head->val == 3);
    }

    SECTION("1 nodes") {
        ListNode *head = new ListNode(1);
        s.reorderList(head);
        REQUIRE(head->val == 1);
    }
}
