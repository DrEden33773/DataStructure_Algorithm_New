/**
 * @file BinarySearch.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief do Binary Search in a sorted array
 * @version 0.1
 * @date 2022-07-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <vector>

class BinarySearch {
public:
    static inline void interface();

private:
    static inline int solution(std::vector<int>& nums, const int& target);
};

/**
 * @brief return the Index (return -1 if not found)
 *
 * @param nums: std::vector<int>&
 * @param target: const int&
 * @return int
 */
int BinarySearch::solution(std::vector<int>& nums, const int& target) {
    if (nums.empty()) {
        return -1; // do it immediately
    }
    // sort nums
    std::sort(nums.begin(), nums.end());
    // binary search
    int resIndex = 0;
    int left     = 0;
    int right    = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            resIndex = mid;
            break;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return resIndex;
}