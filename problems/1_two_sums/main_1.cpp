#include <vector>
#include <cassert>
#include <leetcode_util.h>

#include "solution_1.h"

struct TestCase {
    using output_t = std::vector<int>;

    std::vector<int> input;
    int target = 0;
    std::vector<int> expected_output;

    TestCase(std::vector<int> input, int target, std::vector<int> output)
    : input(std::move(input)), target(target), expected_output(std::move(output)) {

    }
};

std::ostream& operator<<(std::ostream& out, TestCase& test) {
    out << "input=" << test.input << ", target=" << test.target << ", expected=" << test.expected_output;
    return out;
}

int main() {
    leet::TestRunner<Solution, TestCase> runner;
    runner.prepare([](std::vector<TestCase>& test_cases){
        //test cases
        test_cases.push_back(TestCase({2, 7, 11, 15}, 9, {0, 1}));
        test_cases.push_back(TestCase({2, 7, 11, 15}, 26, {2, 3}));
    });
    runner.execute([](TestCase& test, Solution& sol){
        return sol.twoSum(test.input, test.target);
    });
    runner.validate([](TestCase& test, TestCase::output_t& output){
        return output == test.expected_output;
    });
    return runner.run();
}
