/**
 * @file Max_Sum_of_Sub_Array.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief SubArray must be an continuous one! => come from leetcode53
 * @version 0.1
 * @date 2022-07-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>

class Max_Sum_of_Sub {
private:
    inline static int solution(const std::vector<int>& nums);
    inline static int max_of(const int& a, const int& b);
    // inline static int better_solution(const vector<int> &nums);

public:
    inline static void interface();
};

int Max_Sum_of_Sub::max_of(const int& a, const int& b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

void Max_Sum_of_Sub::interface() {
    std::cout << "Please input then array:" << std::endl;
    std::cout << "\t>> ";
    std::vector<int> input;
    int temp;
    while (std::cin >> temp) {
        input.push_back(temp);
    }
    int res = solution(input);
    std::cout << "a.Result: " << res << std::endl;
    // int RES = better_solution(input);
    // cout << "b.Result: " << RES << endl;
}

/**
 * @brief Dynamic_Programming
 *
 * @param nums
 * @return int
 */
int Max_Sum_of_Sub::solution(const std::vector<int>& nums) {
    if (nums.size() == 1) {
        return nums[0];
    }
    int res     = nums[0]; // to be returned
    int sum     = res;     // Σ[LeftPOS, RightPOS)
    int LeftPOS = 0;
    // int RightPOS = 1;
    for (int i = 1; i < nums.size(); ++i) {
        // RightPOS = i;
        int current = nums[i];
        if (current >= 0) { //=> to update
            if (sum <= 0) { //=> update Left_POS & Right_POS
                res     = max_of(res, current);
                sum     = current;
                LeftPOS = i;
                continue;
            } else { //=> update Right_POS
                sum += current;
                res = max_of(res, sum);
            }
        } else { // => possible to update
            // sum += current;
            if (sum <= current) { //=> to update
                res     = max_of(res, current);
                sum     = current;
                LeftPOS = i;
                continue;
            } else { //=> no update
                sum += current;
                res = max_of(res, sum);
            }
        }
    }
    return res;
}