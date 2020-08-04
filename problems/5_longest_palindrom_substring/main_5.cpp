#include <vector>
#include <leetcode_util.h>

#include "solution_5.h"

struct TestCase {

    using output_t = std::string;

    std::string input;
    std::vector<output_t> valid_palindroms;

    TestCase(std::string input, const std::string& palindrom)
            : input(std::move(input)) {
        valid_palindroms.push_back(palindrom);
    }

    TestCase(std::string input, std::vector<std::string> palindroms)
            : input(std::move(input)), valid_palindroms(std::move(palindroms)) {}

};

// print test case
std::ostream& operator<<(std::ostream& out, TestCase& test) {
    out << "input=" << test.input << ", palindrom=" << test.valid_palindroms;
    return out;
}

int main() {
    leet::TestRunner<Solution, TestCase> runner;
    runner.prepare([](std::vector<TestCase>& test_cases){
        //test cases
        test_cases.emplace_back("babad", std::vector<std::string>{"bab", "aba"});
        test_cases.emplace_back("cbbd", "bb");
    });
    runner.execute([](TestCase& test, Solution& sol){
        return sol.longestPalindrome(test.input);
    });
    runner.validate([](TestCase& test, TestCase::output_t& output){
        return std::find(test.valid_palindroms.begin(), test.valid_palindroms.end(), output) != test.valid_palindroms.end();
    });
    return runner.run(100);
}
