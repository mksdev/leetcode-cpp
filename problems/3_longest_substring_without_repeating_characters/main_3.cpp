#include <vector>
#include <leetcode_util.h>

#include "solution_3.h"

struct TestCase {
    using output_t = int;

    std::string input;
    int substring_length = 0;

    TestCase(std::string input, int length)
    : input(std::move(input)), substring_length(length) {}
};

// print test case
std::ostream& operator<<(std::ostream& out, TestCase& test) {
    out << "input=" << test.input << ", length=" << test.substring_length;
    return out;
}

int main() {
    leet::TestRunner<Solution, TestCase> runner;
    runner.prepare([](std::vector<TestCase>& test_cases){
        //test cases
        test_cases.emplace_back("abcabcbb", 3);
        test_cases.emplace_back("bbbbb", 1);
        test_cases.emplace_back("pwwkew", 3);
    });
    runner.execute([](TestCase& test, Solution& sol){
        return sol.lengthOfLongestSubstring(test.input);
    });
    runner.validate([](TestCase& test, TestCase::output_t& output){
        return output == test.substring_length;
    });
    return runner.run(100);
}
