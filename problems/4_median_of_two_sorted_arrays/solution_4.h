//
// Created by Michal Němec on 02/08/2020.
//

#ifndef LEETCODE_SOLUTION_4_H
#define LEETCODE_SOLUTION_4_H

#include <vector>
#include <algorithm>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        if(nums1.size() > nums2.size() ){
            return findMedianSortedArrays(nums2, nums1);
        }

        if(!nums1.empty() && nums2.empty()) {
            auto sz = nums1.size();
            if(sz%2 == 0) {
                return (nums1[sz/2-1] + nums1[sz/2])/2.0;
            } else {
                return static_cast<double>(nums1[sz/2]);
            }
        }

        if(nums1.empty() && !nums2.empty()) {
            auto sz = nums2.size();
            if(sz%2 == 0) {
                return (nums2[sz/2-1] + nums2[sz/2])/2.0;
            } else {
                return static_cast<double>(nums2[sz/2]);
            }
        }

        int x = nums1.size();
        int y = nums2.size();
        double ans = 0.0;
        int low = 0;
        int high = x;

        while(low <= high){
            int partitionx = (low+high)/2;
            int partitiony  = (x+y+1)/2 - partitionx;

            int maxLeftX = (partitionx == 0) ? INT_MIN: nums1[partitionx-1];
            int minRightX = (partitionx == x) ? INT_MAX: nums1[partitionx];

            int maxLeftY = (partitiony == 0) ? INT_MIN: nums2[partitiony-1];
            int minRightY = (partitiony == y) ?  INT_MAX: nums2[partitiony];

            if(maxLeftX <= minRightY && maxLeftY <= minRightX){
                if((x+y)%2 == 0) {
                    auto max_left = std::max(maxLeftX,maxLeftY);
                    auto min_right = std::min(minRightX,minRightY);
                    return (max_left + min_right)/2.0;
                } else {
                    return static_cast<double>(std::max(maxLeftX,maxLeftY));
                }
            } else if(maxLeftX > minRightY){
                high = partitionx-1;
            } else {
                low = partitionx+1;
            }
        }
        return ans;
    }
};

#endif //LEETCODE_SOLUTION_4_H
