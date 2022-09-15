/**
 * @file yanghui_tri.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Give number N, then print YangHui Triangle
 * @version 0.1
 * @date 2022-07-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>

class yanghui_tri {
public:
    static void interface();
    static void solution(const int& num);
};

void yanghui_tri::interface() {
    std::cout << "YangHui Triangle" << std::endl;
    std::cout << "Author >> Eden" << std::endl;
    std::cout << std::endl;
    std::cout << "Please input number (should > 0) => ";
    int input;
    std::cin >> input;
    std::cout << std::endl;
    solution(input);
}

/**
 * @brief No Recursion, only Iteration => Highest Speed!
 *
 * @param num
 */
void yanghui_tri::solution(const int& num) {
    if (num <= 0) {
        throw std::invalid_argument("input <= 0");
    }
    int curr_line = 1;
    std::vector<size_t> current;
    std::vector<size_t> reference;
    while (curr_line <= num) {
        // build from reference
        current.reserve(curr_line);
        if (curr_line == 1) {
            current.emplace_back(1);
        } else if (curr_line == 2) {
            current.emplace_back(1);
            current.emplace_back(1);
        } else {
            current.emplace_back(1);
            for (int curr_POS = 1; curr_POS < curr_line - 1; ++curr_POS) {
                current.emplace_back(reference[curr_POS] + reference[curr_POS - 1]);
            }
            current.emplace_back(1);
        }
        // print current
        for (auto& number : current) {
            std::cout << number << " ";
        }
        std::cout << std::endl;
        // update curr_line
        ++curr_line;
        // current ==move=> reference
        reference = std::move(current);
    }
}