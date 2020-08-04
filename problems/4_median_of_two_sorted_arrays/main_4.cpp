#include <vector>
#include <leetcode_util.h>

#include "solution_4.h"

struct TestCase {
    using output_t = double;

    std::vector<int> nums1;
    std::vector<int> nums2;
    double expected_median;

    TestCase(std::vector<int> nums1, std::vector<int> nums2, double expected_median)
    : nums1(std::move(nums1)), nums2(std::move(nums2)), expected_median(expected_median) {}
};

// print test case
std::ostream& operator<<(std::ostream& out, TestCase& test) {
    out << "nums1=" << test.nums1 << ", nums2=" << test.nums2 << ", median=" << test.expected_median;
    return out;
}

int main() {
    leet::TestRunner<Solution, TestCase> runner;
    runner.prepare([](std::vector<TestCase>& test_cases){
        //test cases
        test_cases.push_back(TestCase({1, 3}, {}, 2.0));
        test_cases.push_back(TestCase({}, {1, 3}, 2.0));
        test_cases.push_back(TestCase({1, 3}, {2}, 2.0));
        test_cases.push_back(TestCase({1, 2}, {3, 4}, 2.5));
    });
    runner.execute([](TestCase& test, Solution& sol){
        return sol.findMedianSortedArrays(test.nums1, test.nums2);
    });
    runner.validate([](TestCase& test, TestCase::output_t& output){
        return output == test.expected_median;
    });
    return runner.run();
}
