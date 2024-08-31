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

        int index = 0;
        while (index != left - 1) {
            index++;
            current = current->next;
        }
    }
};