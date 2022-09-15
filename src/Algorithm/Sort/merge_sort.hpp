/**
 * @file merge_sort.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief merge_sort => accending oreder
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>

class MergeSort {
public:
    static inline void interface();

    static inline void merge(
        std::vector<int>& nums, int left, int mid, int right
    );
    static void mergeSort(
        std::vector<int>& nums, int left, int right
    );
};

// T(n) = Theta(n)
void MergeSort::merge(
    std::vector<int>& nums,
    int left,
    int mid,
    int right
) {
    int len = right - left + 1;
    std::vector<int> tmp(len);
    int i = left;    // i <=> POS of Left_Part_Array
    int j = mid + 1; // j <=> POS of Right_Part_Array
    int k = 0;       // k <=> POS of Temp_Array

    // `two-finger` algorithm
    /** pick up the lower value of two, push it into tmp */
    while (i <= mid && j <= right) {
        // push the lower one
        if (nums[i] < nums[j]) {
            tmp[k] = nums[i];
            ++i;
        } else {
            tmp[k] = nums[j];
            ++j;
        }
        ++k;
    }

    // do the rest in left part
    while (i <= mid) {
        tmp[k] = nums[i];
        ++i;
        ++k;
    }
    // do the rest in right part
    while (j <= right) {
        tmp[k] = nums[j];
        ++j;
        ++k;
    }

    // push the sorted back to nums => start from `left
    for (int i = 0; i < len; ++i) {
        nums[left + i] = tmp[i];
    }
}

// T(n) = 2T(n/2) + Theta(n) => Theta(nlogn)
void MergeSort::mergeSort(std::vector<int>& nums, int left, int right) {
    if (left < right) {
        // left == right ==imply=> only 1 element in the sub vector
        // that vector must be ordered, do not need to sort anymore
        int mid = (left + right) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
        // have to merge the two above sub vector (each recursive call)
    }
}

// T(n) = O(nlogn)
