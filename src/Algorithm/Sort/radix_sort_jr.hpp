/**
 * @file radix_sort_jr.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief radix_sort_jr
 * @version 0.1
 * @date 2022-07-17
 *
 * @copyright Copyright (c) 2022
 *
 */

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>

class RadixSortJr {
private:
    struct tuple {
        int a = -1; // a = val / n
        int b = -1; // b = val % n
    };
    struct bond {
        tuple tran;
        int val = -1;
    };
    enum KEY {
        a,
        b,
    };
    std::vector<std::vector<bond>> DAA; // Direct Access Array
    std::vector<bond> bondVec;          // Array store bonds

    // functions
    void init_bondVec(std::vector<int>& input);
    void DAA_Sort(KEY input, const int& ToSortLen);
    void abstract_from_bondVec(std::vector<int>& input);
    void println_Vec(std::vector<int>& input);

public:
    void interface();
    void solution(std::vector<int>& input);
};

/**
 * @brief radix_accending_sort
 * @attention input.size() or 0 <= input[i] < (input.size())^2 , input[i]>=0
 * @param input
 */
void RadixSortJr::solution(std::vector<int>& input) {
    static const int InputLen = static_cast<int>(input.size());
    // initialize bondVec
    init_bondVec(input);
    // DAA_Sort
    DAA_Sort(b, InputLen);
    DAA_Sort(a, InputLen);
    // input <==pull== bondVec
    abstract_from_bondVec(input);
}

void RadixSortJr::init_bondVec(std::vector<int>& input) {
    const int InputLen = static_cast<int>(input.size());
    // initialize bondVec
    bondVec.reserve(InputLen);
    for (auto& num : input) {
        bond temp;
        temp.tran.a = num / InputLen;
        temp.tran.b = num % InputLen;
        temp.val    = num;
        bondVec.emplace_back(temp); // emplace => place != push
    }
}

void RadixSortJr::DAA_Sort(KEY input, const int& ToSortLen) {
    DAA.reserve(ToSortLen);
    // initialize DAA => necessary
    std::vector<bond> init_elem {};
    for (int i = 0; i < ToSortLen; i++) {
        DAA.emplace_back(init_elem);
    }
    // bondVec ==push=> DAA
    for (auto& bond : bondVec) {
        int key;
        if (input == a) {
            key = bond.tran.a;
        } else {
            key = bond.tran.b;
        }
        DAA[key].push_back(bond);
    }
    // bondVec <==pull== DAA
    int scannedNums = 0;
    for (auto& bonds : DAA) {
        if (scannedNums == ToSortLen) {
            break;
        }
        if (bonds.size() == 0) {
            continue;
        }
        for (auto& bond : bonds) {
            bondVec[scannedNums] = bond;
            scannedNums += 1;
        }
    }
    // clear DAA => necessary
    DAA.erase(DAA.begin(), DAA.end());
}

void RadixSortJr::abstract_from_bondVec(std::vector<int>& input) {
    const int InputLen = static_cast<int>(input.size());
    int scannedNums    = 0;
    for (auto& bond : bondVec) {
        if (scannedNums == InputLen) {
            break;
        }
        input[scannedNums] = bond.val;
        scannedNums += 1;
    }
}

void RadixSortJr::println_Vec(std::vector<int>& input) {
    for (auto& num : input) {
        std::cout << num << " ";
    }
    std::cout << "\b \b";
    std::cout << std::endl;
}

void RadixSortJr::interface() {
    std::vector<int> test { 1, 2, 4, 1, 6, 7, 5, 10, 9, 15, 30 };
    println_Vec(test);
    solution(test);
    println_Vec(test);
}