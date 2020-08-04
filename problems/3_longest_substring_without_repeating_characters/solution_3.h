//
// Created by Michal Němec on 02/08/2020.
//

#ifndef LEETCODE_SOLUTION_3_H
#define LEETCODE_SOLUTION_3_H

#include <string>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        if(s.empty()) return 0;
        int len = 0;
        int sz = s.size();
        int i = 0;
        int prev_start = 0;
        while(true) {
            int ascii[256] = {};
            prev_start = i;
            for(; i != sz; ++i) {
                auto& actual_char = s[i];
                auto& val = ascii[static_cast<int>(actual_char)];
                if(val != 0) {
                    auto len_sub = i - prev_start;
                    if(len_sub > len) {
                        len = len_sub;
                    }
                    for(int b = i-1; b != -1; --b) {
                        if (actual_char == s[b]) {
                            i = b+1;
                            break;
                        }
                    }
                    break;
                }
                ++val;
            }
            if(i == sz) {
                auto len_sub = i - prev_start;
                if(len_sub > len) {
                    len = len_sub;
                }
                break;
            }
        }
        return len;
    }
};

#endif //LEETCODE_SOLUTION_3_H
