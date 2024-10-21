//
// Created by stellaura on 20/10/24.
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
    ListNode *reverseKGroup(ListNode *head, int k) {
        // calculate length
        int length = 1;
        auto current = head;
        while (current->next) {
            current = current->next;
            length++;
        }

        // add head
        auto node0 = new ListNode(0);
        node0->next = head;
        // initialize prev curr next
        ListNode *prev = nullptr;
        current = node0;
        ListNode *next = head;

        // 每一个内层循环完成之后
        // prev curr next 保持不变
        //
        // 不能先改然后                                                                                               
        for (int i = 0; i < length / k; i++) {
            // the node before each k nodes
            auto before_block_begin = current;
            // i.e. the first of each k nodes
            auto block_end = next;
            for (int j = 0; j < k; j++) {
                prev = current;
                current = next;
                next = next->next;
                // reverse node from i*k+j
                current->next = prev;
            }
            before_block_begin->next = current;
            block_end->next = next;
            current = block_end;
//            prev = nullptr; // 可以不写 反正马上就会更新这个值
        }

        auto ret = node0->next;
        delete node0;
        return ret;
    }
};

TEST_CASE() {
    Solution s{};

    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    SECTION("test 1") {
        auto ret = s.reverseKGroup(head, 2);
        REQUIRE(ret->val == 2);
        ret = ret->next;
        REQUIRE(ret->val == 1);
        ret = ret->next;
        REQUIRE(ret->val == 4);
        ret = ret->next;
        REQUIRE(ret->val == 3);
        ret = ret->next;
        REQUIRE(ret->val == 5);
    }

    SECTION("test 2") {
        auto ret = s.reverseKGroup(head, 3);
        REQUIRE(ret->val == 3);
        ret = ret->next;
        REQUIRE(ret->val == 2);
        ret = ret->next;
        REQUIRE(ret->val == 1);
        ret = ret->next;
        REQUIRE(ret->val == 4);
        ret = ret->next;
        REQUIRE(ret->val == 5);
    }

    SECTION("test 3") {
        auto ret = s.reverseKGroup(head, 5);
        REQUIRE(ret->val == 5);
        ret = ret->next;
        REQUIRE(ret->val == 4);
        ret = ret->next;
        REQUIRE(ret->val == 3);
        ret = ret->next;
        REQUIRE(ret->val == 2);
        ret = ret->next;
        REQUIRE(ret->val == 1);
    }
}

TEST_CASE("one element") {
    Solution s{};
    ListNode *head = new ListNode(1);

    SECTION("test 1") {
        auto ret = s.reverseKGroup(head, 1);
        REQUIRE(ret->val == 1);
    }

    SECTION("test 2") {
        auto ret = s.reverseKGroup(head, 3);
        REQUIRE(ret->val == 1);
    }
}

TEST_CASE("two element") {
    Solution s{};
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);

    SECTION("test 1") {
        auto ret = s.reverseKGroup(head, 1);
        REQUIRE(ret->val == 1);
        ret = ret->next;
        REQUIRE(ret->val == 2);
    }

    SECTION("test 2") {
        auto ret = s.reverseKGroup(head, 2);
        REQUIRE(ret->val == 2);
        ret = ret->next;
        REQUIRE(ret->val == 1);
    }
}