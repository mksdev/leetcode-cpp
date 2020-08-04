//
// Created by Michal Němec on 02/08/2020.
//

#ifndef LEETCODE_SOLUTION_2_H
#define LEETCODE_SOLUTION_2_H

#include "ListNode.h"

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* base = new ListNode();
        ListNode* actual = base;

        int carry = 0;
        bool l1_null = false;
        bool l2_null = false;

        while(true) {
            auto digit_1 = l1_null ? 0 : l1->val;
            auto digit_2 = l2_null ? 0 : l2->val;

            auto sum = digit_1 + digit_2 + carry;
            auto sum_digit = sum%10;
            carry = sum/10;

            actual->val = sum_digit;

            if(!l1_null) {
                l1 = l1->next;
                l1_null = l1 == nullptr;
            }

            if(!l2_null) {
                l2 = l2->next;
                l2_null = l2 == nullptr;
            }

            if(l1_null && l2_null) {
                if(carry != 0) {
                    actual->next = new ListNode();
                    actual = actual->next;
                    actual->val = carry;
                }
                break;
            }

            actual->next = new ListNode();
            actual = actual->next;
        }

        return base;
    }
};

#endif //LEETCODE_SOLUTION_2_H
