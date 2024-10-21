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
    ListNode *middleNode(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        int count = 0;
        while (fast->next) {
            if (count % 2 == 0) {
                slow = slow->next;
            }
            fast = fast->next;
            count++;
        }
        return slow;
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

        auto ret = s.middleNode(head);
        REQUIRE(ret->val == 3);
    }

    SECTION("6 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = new ListNode(6);

        auto ret = s.middleNode(head);
        REQUIRE(ret->val == 4);
    }

    SECTION("1 nodes") {
        ListNode *head = new ListNode(1);

        auto ret = s.middleNode(head);
        REQUIRE(ret->val == 1);
    }

    SECTION("2 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);

        auto ret = s.middleNode(head);
        REQUIRE(ret->val == 2);
    }

    SECTION("3 nodes") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);

        auto ret = s.middleNode(head);
        REQUIRE(ret->val == 2);
    }
}