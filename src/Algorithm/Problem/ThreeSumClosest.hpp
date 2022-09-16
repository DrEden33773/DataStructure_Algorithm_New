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

        /**
         * @brief find the index whose element is closest to the given one
         *        THIS FUNCTION MAY NOT BE CORRECT !!!
         */
        auto findClosestIndex = [](vector<int>& input, int& toFind) -> int {
            int index = 0;
            int left  = 0;
            int right = input.size() - 1;
            while (left < right) {
                int mid = (left + right) / 2;
                if (input[mid] == toFind) {
                    index = mid;
                    break;
                } else if (input[mid] < toFind) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return index;
        };
        int closestIndex = findClosestIndex(nums, target);
        // 4. see the index
        if (closestIndex == 0) {
            res = (nums[0] + nums[1] + nums[2]);
        } else if (closestIndex == nums.size() - 1) {
            res = (nums[closestIndex] + nums[closestIndex - 1] + nums[closestIndex - 2]);
        } else {
            // this is the worst case
            //
            // now you need to find two nums in remaining vector
            // whose sum should be the closest to 0
            auto findRemainSumClosestToZero =
                [](vector<int>& Arr, int& subIndex) -> int {
                int closestSum = 0;
                return closestSum;
            };
        }
        return res;
    }
};
