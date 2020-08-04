#include <vector>
#include <cassert>
#include <leetcode_util.h>

#include "ListNode.h"
#include "solution_2.h"

struct TestCase {
    using output_t = ListNode*;

    int num1 = 0;
    int num2 = 0;

    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;
    ListNode* expected = nullptr;

    TestCase(int num1, int num2)
    : num1(num1), num2(num2),
      l1(ListNode::new_number(num1)), l2(ListNode::new_number(num2)),
      expected(ListNode::new_number(num1 + num2)) {
        assert(l1);
        assert(l2);
        assert(expected);
    }

    TestCase(const TestCase& rhs)
    : num1(rhs.num1), num2(rhs.num2),
      l1(ListNode::new_number(rhs.num1)), l2(ListNode::new_number(rhs.num2)),
      expected(ListNode::new_number(rhs.num1 + rhs.num2)) {
        assert(l1);
        assert(l2);
        assert(expected);
    }

    TestCase(TestCase&& rhs) noexcept
    : num1(rhs.num1), num2(rhs.num2),
      l1(rhs.l1), l2(rhs.l2),
      expected(rhs.expected) {
        rhs.num1 = 0;
        rhs.num2 = 0;
        rhs.l1 = nullptr;
        rhs.l2 = nullptr;
        rhs.expected = nullptr;
    }

    ~TestCase() {
        ListNode::delete_number(l1);
        ListNode::delete_number(l2);
        ListNode::delete_number(expected);
    }
};

std::ostream& operator<<(std::ostream& out, TestCase& test) {
    return out << "l1=" << test.l1 << ", l2=" << test.l2 << ", expected=" << test.expected;
}

int main() {
    leet::TestRunner<Solution, TestCase> runner;
    runner.prepare([](std::vector<TestCase>& test_cases){
        //test cases
        test_cases.emplace_back(10, 10);
        test_cases.emplace_back(24, 38);
    });
    runner.execute([](TestCase& test, Solution& sol){
        return sol.addTwoNumbers(test.l1, test.l2);
    });
    runner.validate([](TestCase& test, TestCase::output_t& output){
        return *output == *test.expected;
    });
    runner.cleanup([](TestCase& test, TestCase::output_t& output){
        // output is allocated within the test
        ListNode::delete_number(output);
    });
    return runner.run(10);
}
