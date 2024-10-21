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
    // 快慢指针
    // 巧妙的题
    // 无法独立想出
    // 看 obsidian 的解析
    ListNode *detectCycle(ListNode *head) {
        if(head == nullptr){
            return nullptr;
        }

        auto slow = head;
        auto fast = head;

        // 必须用同时 +1 +2的版本
        // 否则可能会在 +0 +1的时候相遇，此时 fast != 2slow
        do {
            slow = slow->next;
            fast = fast->next;
            if (fast == nullptr) {
                return nullptr;
            }
            fast = fast->next;
            if (fast == nullptr) {
                return nullptr;
            }
        } while (slow != fast);

        // now slow == fast
        // the length is a+b
        // a+b = k*(length of ring)
        auto new_head = head;
        while (new_head != slow) {
            slow = slow->next;
            new_head = new_head->next;
        }

        return new_head;
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
        REQUIRE(s.detectCycle(head) == nullptr);
    }

    SECTION("no loop 1 node") {
        ListNode *head = new ListNode(1);
        REQUIRE(s.detectCycle(head) == nullptr);
    }

    SECTION("has loop 5 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = head->next->next;
        REQUIRE(s.detectCycle(head) == head->next->next);
    }

    SECTION("has loop 5 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = head->next->next->next->next;
        REQUIRE(s.detectCycle(head) == head->next->next->next->next);
    }

    SECTION("has loop 5 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = head;
        REQUIRE(s.detectCycle(head) == head);
    }

    SECTION("has loop 1 node") {
        ListNode *head = new ListNode(1);
        head->next = head;
        REQUIRE(s.detectCycle(head) == head);
    }

    SECTION("no loop 1 node") {
        ListNode *head = new ListNode(1);
        REQUIRE(s.detectCycle(head) == nullptr);
    }
}