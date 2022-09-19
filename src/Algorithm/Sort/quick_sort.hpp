/**
 * @file quick_sort.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief quick sort
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

// [-1,4,2,6,7,-6]

template <typename T>
class quick_sort {
private:
    // quick_sort
    static void QuickSort(std::vector<T>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int pivot = partition(nums, left, right);
        quick_sort(nums, left, pivot - 1);
        quick_sort(nums, pivot + 1, right);
    }

    // partition
    static int partition(std::vector<T>& nums, int left, int right) {
        int pivot = nums[left];
        int l     = left + 1;
        int r     = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot) {
                std::swap(nums[l++], nums[r--]);
            }
            if (nums[l] >= pivot) {
                ++l;
            }
            if (nums[r] <= pivot) {
                --r;
            }
        }
        std::swap(nums[left], nums[r]);
        return r;
    }

    // example
    static void example() {
        std::cout << std::endl;
        std::vector<int> test = { -1, 4, 2, 6, 7, -6 };
        quick_sort(test, 0, static_cast<int>(test.size()) - 1);
        for (auto& i : test) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
};