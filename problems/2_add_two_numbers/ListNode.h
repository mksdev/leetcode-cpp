//
// Created by Michal Němec on 02/08/2020.
//

#ifndef LEETCODE_LISTNODE_H
#define LEETCODE_LISTNODE_H

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    static ListNode* new_number(int val) {
        if(val == 0) {
            return new ListNode();
        }
        auto* root = new ListNode();
        assert(root);
        auto* node = root;
        {
            int digit = val%10;
            node->val = digit;
            val = val/10;
        }
        while(val != 0) {
            // create new node and connect to current one
            auto* new_node = new ListNode();
            assert(new_node);
            node->next = new_node;
            node = new_node;

            // save digit on actual position
            int digit = val%10;
            node->val = digit;
            val = val/10;
        }
        return root;
    }

    static void delete_number(ListNode* root) {
        std::size_t level = 0;
        auto* ptr = root;
        while(ptr != nullptr) {
            ++level;
            assert(level != 10000);
            auto next = ptr->next;
            delete ptr;
            ptr = next;
        }
    }

    bool operator==(ListNode& l2) {
        auto* ptr1 = this;
        auto* ptr2 = &l2;
        do {
            if(ptr1 == nullptr && ptr2 == nullptr) {
                break;
            }
            if(ptr1 == nullptr && ptr2 != nullptr) return false;
            if(ptr1 != nullptr && ptr2 == nullptr) return false;
            if(ptr1->val == ptr2->val) {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            } else {
                return false;
            }
        } while(true);
        return true;
    }

};

std::ostream& operator<<(std::ostream& out, ListNode& test) {
    auto* ptr = &test;
    out << "{";
    while(ptr != nullptr) {
        out << ptr->val;
        ptr = ptr->next;
        if(ptr != nullptr) {
            out << ", ";
        }
    }
    out << "}";
    return out;
}

std::ostream& operator<<(std::ostream& out, ListNode* test) {
    if(test == nullptr) {
        out << "nullptr";
        return out;
    }
    return out << *test;
}

#endif //LEETCODE_LISTNODE_H
