//
// Created by Michal Němec on 02/08/2020.
//

#ifndef LEETCODE_SOLUTION_1_H
#define LEETCODE_SOLUTION_1_H

#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> out;
        out.resize(2);
        auto sz = nums.size();
        for(int i = 0; i != sz; ++i) {
            auto& num_i = nums[i];
            for(int j = i+1; j != sz; ++j) {
                auto& num_j = nums[j];
                if(num_i + num_j == target) {
                    out[0] = i;
                    out[1] = j;
                    return out;
                }
            }
        }
        return out;
    }
};

#endif //LEETCODE_SOLUTION_1_H
