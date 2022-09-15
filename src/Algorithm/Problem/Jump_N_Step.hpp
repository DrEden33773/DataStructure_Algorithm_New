/**
 * @file Jump_N_Step.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Jump 1 or 2 steps once, total N steps, how many methods to the top?
 * @version 0.1
 * @date 2022-07-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>

class N_Step {
public:
    static inline void interface();

private:
    [[maybe_unused]] inline static int solution(const int& input);
    inline static int better_solution(const int& input);
    inline static int best_solution(const int& input);
};

void N_Step::interface() {
    std::cout << "Input number of steps(N) >> ";
    int input = 0;
    std::cin >> input;
    if (input <= 0) {
        throw std::invalid_argument("input should >= 1");
    }
    int res   = better_solution(input);
    int res_2 = best_solution(input);
    std::cout << "The result (better_solution) is >> " << res << std::endl;
    std::cout << "The result (best_solution) is >> " << res_2 << std::endl;
    std::cout << std::endl;
}

/**
 * @brief back_tracing => recursion
 *
 * @param input
 * @return int
 */
int N_Step::solution(const int& input) {
    if (input < 0) {
        return 0;
    }
    int res = 1;
    if (input == 0) { //=> stay, without any movements => this is `a` method
        return res;
    }
    res = solution(input - 1) + solution(input - 2);
    return res;
}

/**
 * @brief dynamic_programming => iterate
 *
 * @param input
 * @return int
 */
int N_Step::better_solution(const int& input) {
    if (input == 1 || input == 0) {
        return 1;
    }
    // try to iterate in one function this time!
    std::vector<int> result_vec;
    for (int i = 0; i <= input; ++i) {
        if (i <= 1) {
            result_vec.push_back(1);
        } else {
            result_vec.push_back(result_vec[i - 1] + result_vec[i - 2]);
            if (result_vec[i] < result_vec[i - 1]) {
                std::cout << "Data overflowed while i = " << i << std::endl;
                throw std::overflow_error("Error_type: overflow_error");
            }
        }
    }
    return result_vec[result_vec.size() - 1];
    // in this case, the question is equal to a Fibonacci list
}

/**
 * @brief dynamic_programming, aborting vector => iterate + state transition
 *
 * @param input
 * @return int
 */
int N_Step::best_solution(const int& input) {
    if (input == 1 || input == 0) {
        return 1;
    }
    int _2 = 1; // the second behind current
    int _1 = 1; // the first behind current
    int _0 = 1; // the current
    for (int i = 2; i <= input; ++i) {
        _0 = _1 + _2;
        _2 = _1;
        _1 = _0;
    }
    if (_0 < _1) {
        throw std::overflow_error("Data overflowed");
    }
    return _0;
}
