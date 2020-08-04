//
// Created by Michal Němec on 02/08/2020.
//

#ifndef LEETCODE_UTIL_H
#define LEETCODE_UTIL_H

#include <iostream>
#include <string>
#include <functional>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <set>

template<typename T>
std::ostream& print_stl(std::ostream& os, const T& obj) {
    auto it = obj.begin();
    auto it_end = obj.end();
    os << "{";
    if(it != it_end) {
        while(true) {
            os << *it;
            if(++it == it_end) {
                break;
            } else {
                os << ", ";
            }
        }
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& obj) {
    return print_stl(os, obj);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& obj) {
    return print_stl(os, obj);
}

namespace leet {

using clock = std::chrono::high_resolution_clock;

/**
 * String format std::chrono::duration<> to human readable string with automatic scaling and without any compression
 * Resolution supported up to nanoseconds
 * When formated time has trailing zeros, they re automatically discarded
 *
 * Example usage:
 *      auto start = std::chrono::high_resolution_clock::now();
 *      .. some computation ...
 *      auto start = std::chrono::high_resolution_clock::now();
 *      auto printable_string = dur2str(end - start);
 *
 * @tparam Rep
 * @tparam Period
 * @param diff
 * @return duration format: hh::mm::ss.mmm'uuu'nnnn, trailing zeroes are omitted
 */
template <class Rep, class Period>
std::string dur2str(const std::chrono::duration<Rep, Period>& diff) {
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
    auto wall_time = ns.count();
    if(wall_time == 0) {
        return "0 ns";
    }
    auto nano = wall_time%1000LL;
    auto micro = (wall_time/1000LL)%1000LL;
    auto milli = (wall_time/1000000LL)%1000LL;
    auto secs_base = wall_time/1000000000LL;
    auto hours = secs_base/3600LL;
    auto minutes = (secs_base/60LL)%60LL;
    auto seconds = secs_base%60LL;

    bool enable_tm[6];
    bool enable_tm_back[6];
    int64_t enable_tm_vals[6] = { nano, micro, milli, seconds, minutes, hours };
    for(int i = 0; i != 6; ++i) {
        enable_tm_back[i] = (enable_tm_vals[i] == 0);
        enable_tm[i] = (enable_tm_vals[i] > 0);
    }
    const char* enable_tm_end[6] = { "ns", "us", "ms", "s", "min", "h"};
    uint8_t enable_tm_sizes[6] = { 3, 3, 3, 2, 2, 0};
    uint8_t enable_tm_separator[6] = { '\0', '\'', '\'', '.', ':', ':'};

    // formatting is done in format
    // format: hh::mm::ss.mmm'uuu'nnnn
    //    idx:  5   4   3   2   1    0
    // we want to exclude highest zero values
    {
        // enable_tm contains all positions that will be formatted
        // eg. 00:30:00.333222000 enable_tm would contain
        // enable_tm[0] = false
        // enable_tm[1] = true
        // enable_tm[2] = true
        // enable_tm[3] = false
        // enable_tm[4] = true
        // enable_tm[5] = false
        //
        // after loop we set true value to all before minutes
        // enable_tm[0] = true
        // enable_tm[1] = true
        // enable_tm[2] = true
        // enable_tm[3] = true
        // enable_tm[4] = true
        // enable_tm[5] = false
        //
        // these values will be formatted
        auto prev = enable_tm[5];
        for(uint8_t i = 4; i != 0; i--) {
            if(prev) {
                enable_tm[i] = true;
            }
            prev = enable_tm[i];
        }
    }

    // find first nonzero element in time elements
    // format: hh::mm::ss.mmm'uuu'nnnn
    //    idx:  5   4   3   2   1    0
    // if nanosecods and microseconds are zero then we want to exclude them
    // stop_i would be 2
    // from previous example if we are printing 00:30:00.333222000
    // we would format only values 30:00.333222
    //  ns: enable_tm[0] = true -> nanoseconds contains zero
    //  us: enable_tm[1] = true -> format only microseconds to minutes
    //  ms: enable_tm[2] = true
    //   s: enable_tm[3] = true
    // min: enable_tm[4] = true
    //   h: enable_tm[5] = false
    uint8_t stop_i = 0;
    for(; stop_i != 6; stop_i++) {
        if(!enable_tm_back[stop_i]) break;
    }

    std::ostringstream oss;
    {
        auto prev = false;
        const char* end = nullptr;
        for(int8_t i = 5; i != -1; i--) {
            if(enable_tm[i]) {
                char sep = enable_tm_separator[i];
                if(!prev) {
                    oss << enable_tm_vals[i];
                    if(sep == '\'') {
                        // separator '\'' is for numbers behand decimal place
                        // if time is sub-seconds we want to use '.' instead
                        // eg. 32'333 us -> 32.333 us
                        sep = '.';
                    }
                    end = enable_tm_end[i];
                } else {
                    // i < 3 is for nano, micro, mili sec (idx 0,1,2)
                    if(i < 3 && i == stop_i) {
                        // when formating last element behind decimal place
                        // cutoff all zeroes at the end
                        // 1.101'100 ms -> 1.101'1 ms
                        auto reduced = enable_tm_vals[i];
                        int places_zero = 3;
                        while(places_zero != 0) {
                            if(reduced % 10 == 0) {
                                reduced /= 10;
                                --places_zero;
                            } else {
                                break;
                            }
                        }
                        if(places_zero > 0) {
                            oss << std::setfill('0') << std::setw(places_zero) << reduced;
                            //oss << fmt::format("{:0>{}}", reduced, places_zero);
                        }
                    } else {
                        oss << std::setfill('0') << std::setw(enable_tm_sizes[i]) << enable_tm_vals[i];
                        //oss << fmt::format("{:0>{}}", enable_tm_vals[i], enable_tm_sizes[i]);
                    }
                }
                if(i > stop_i) {
                    if(sep != '\0') {
                        oss << sep;
                    }
                }
            }
            if(i == stop_i) {
                break;
            }
            prev = enable_tm[i];
        }
        if(end != nullptr) {
            oss << " " << end;
        } else {
            // should not happen
            oss << "0 ns";
        }
    }
    return oss.str();
}

template<typename TestCase, typename Solution>
using apply_fn_t = std::function<bool(TestCase&, Solution&)>;

template<typename TestCase>
using prepare_fn_t = std::function<void(std::vector<TestCase>&)>;

template<typename Solution, typename TestCase>
class TestRunner {

    using test_output_t = typename TestCase::output_t;

    prepare_fn_t<TestCase> prepare_test_case_fn_;
    std::function<test_output_t(TestCase&, Solution&)> execute_fn_;
    std::function<bool(TestCase&, test_output_t&)> validate_fn_;
    std::function<void(TestCase&, test_output_t&)> cleanup_cb_;

    std::vector<TestCase> test_cases_;
    Solution solution_;

public:

    /**
     * Initialize all test cases that will be run on given implementation
     * @param cb
     */
    void prepare(prepare_fn_t<TestCase> cb) {
        prepare_test_case_fn_ = std::move(cb);
    }

    /**
     * Execute test data set on given implementation
     * @param cb
     */
    void execute(std::function<test_output_t(TestCase&, Solution&)> cb) {
        execute_fn_ = std::move(cb);
    }

    /**
     * Process output of the test and validate if test passed
     * @param cb
     */
    void validate(std::function<bool(TestCase&, test_output_t&)> cb) {
        validate_fn_ = std::move(cb);
    }

    /**
     * In case of dynamic allocation inside implementation we should cleanup allocated memory here
     */
    void cleanup(std::function<void(TestCase&, test_output_t&)> cb) {
        cleanup_cb_ = std::move(cb);
    }

    /**
     * main run entry point that will execute all test cases given some implementation
     * @param repeate_time
     * @return
     */
    int run(std::size_t repeate_time = 1) {
        auto prepare_fn = prepare_test_case_fn_;
        if(!prepare_fn) {
            std::cerr << "no prepare function set\n";
            return 1;
        }
        auto execute_fn = execute_fn_;
        if(!execute_fn) {
            std::cerr << "no execute function set\n";
            return 1;
        }
        auto validate_fn = validate_fn_;
        if(!validate_fn) {
            std::cerr << "no validate function set\n";
            return 1;
        }
        auto cleanup_fn = cleanup_cb_;

        prepare_fn(test_cases_);
        std::size_t valid_tests = 0;
        auto total_tests = test_cases_.size();

        auto start = std::chrono::high_resolution_clock::now();
        if(!test_cases_.empty()) {
            std::for_each(test_cases_.begin(), test_cases_.end(), [&](TestCase& test){

                std::chrono::duration<long long int, std::nano> run_time{0};

                auto all_valid = true;
                std::set<std::string> outputs_print;

                // run the same test case repeatedly co obtain average runtime
                for(std::size_t i = 0; i != repeate_time; ++i) {
                    // execute and save runtime
                    auto start_exec = clock::now();
                    auto output = execute_fn(test, solution_);
                    auto end_exec = clock::now();
                    run_time += end_exec - start_exec;

                    // validate test
                    auto valid = validate_fn(test, output);
                    if(all_valid && !valid) {
                        all_valid = false;
                    }

                    // save test output to string
                    std::ostringstream oss;
                    oss << output;
                    outputs_print.insert(oss.str());

                    // free allocated memmory from test
                    if(cleanup_fn) cleanup_fn(test, output);
                }
                valid_tests += all_valid ? 1 : 0;

                std::cout << test << " -> output=";
                if(outputs_print.size() == 1) {
                    std::cout << *outputs_print.begin();
                } else {
                    std::cout << "[" << repeate_time << "]" << outputs_print;
                }
                std::cout << " ... " << (all_valid ? "OK" : "FAILED");
                if(repeate_time == 1) {
                    std::cout << " in " << leet::dur2str(run_time) << "\n";
                } else {
                    std::cout << " in avg " << leet::dur2str(run_time / repeate_time) << "\n";
                }
            });
        }
        auto end = std::chrono::high_resolution_clock::now();

        bool all_pased = valid_tests == total_tests;
        std::cout << "Results " << valid_tests << "/" << total_tests << "\n";
        std::cout << (all_pased ? "PASSED" : "ERROR") << " in " << dur2str(end - start)  << "\n";
        return all_pased ? 0 : 1;
    }

};

}

#endif //LEETCODE_UTIL_H
