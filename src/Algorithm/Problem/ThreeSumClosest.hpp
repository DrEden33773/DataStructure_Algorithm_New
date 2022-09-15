/**
 * @file ThreeSumClosest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
        Given an integer array nums of length n and an integer target,
        find three integers in nums such that the sum is closest to target

        Return the sum of the three integers

        You may assume that each input would have exactly one solution
 *
 * @version 0.1
 * @date 2022-09-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief
    Input: nums = [-1,2,1,-4] => [-4,-1,1,2] , target = 1
    Output: 2
    Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 *
 */
class ThreeSumClosest {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 0;
        // 1. sort the vector (ascending order)
        sort(
            nums.begin(),
            nums.end(),
            [](int& a, int& b) { return a < b; }
        );
        // 2. all zero occasion
        if (*nums.begin() == 0 && *nums.end() == 0) {
            return 0;
        }
        // 3. find the closest element in the vector
        auto closestIndex = [](vector<int>& input) -> int {
            int index = 0;
            return index;
        };
        return res;
    }
};
