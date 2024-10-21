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
    bool hasCycle(ListNode *head) { return solution3(head); }

    // 暴力 题目的链表的最大长度是 10000
    // 显然这个题目的复杂度是 O(n) 因此直接遍历一遍，看是否循环即可
    // 但是这个对于 ACM 格式之类的并不合适
    // 因为ACM会一次输入多组
    bool solution1(ListNode *head) {
        int length = 0;
        auto current = head;
        while (current) {
            if (length >= 10100) {
                return true;
            }
            current = current->next;
            length++;
        }
        return false;
    }

    // 这个题根本不需要map
    // 快慢指针
    bool solution2(ListNode *head) {
        auto slow = head;
        auto fast = head;
        int length = 0;
        while (fast) {
            // 第一步不能走
            if (length % 2) {
                slow = slow->next;
            }
            length++;
            fast = fast->next;
            if (fast == slow) {
                return true;
            }
        }
        return false;
    }

    // fast and slow pointer version 2
    bool solution3(ListNode *head) {
        auto slow = head;
        auto fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next;
            fast = fast->next;
            if (fast == slow) {
                return true;
            }
        }
        return false;
    }

    // version 3, amost same as version 2
    bool solution4(ListNode *head) {
        if (head == nullptr)
            return false;
        auto slow = head;
        auto fast = head;

        do {
            slow = slow->next;
            fast = fast->next;
            if (fast == nullptr) {
                return false;
            }
            fast = fast->next;
            if (fast == nullptr) {
                return false;
            }
        } while (fast != slow);

        return true;
    }
};

TEST_CASE() {
    Solution s;

    SECTION("no loop 5 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        REQUIRE(s.hasCycle(head) == false);
    }

    SECTION("no loop 1 node") {
        ListNode *head = new ListNode(1);
        REQUIRE(s.hasCycle(head) == false);
    }

    SECTION("has loop 5 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = head->next->next;
        REQUIRE(s.hasCycle(head) == true);
    }

    SECTION("has loop 5 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = head->next->next;
        REQUIRE(s.hasCycle(head) == true);
    }

    SECTION("has loop 5 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = head;
        REQUIRE(s.hasCycle(head) == true);
    }

    SECTION("has loop 1 nodes") {
        ListNode *head = new ListNode(1);
        head->next = head;
        REQUIRE(s.hasCycle(head) == true);
    }
}