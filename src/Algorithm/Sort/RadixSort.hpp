/**
 * @file RadixSort.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief RadixSort
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

class RadixSort {
private:
    struct bond {
        vector<int> bitTable = {};
        int val              = -1;
    };

    vector<vector<bond>> DAA; // Direct Access Array
    vector<bond> bondVec;     // Array store bonds
    int highest_bit_POS = -1;

    void init_bondVec(vector<int>& input) {
        const int InputLen = static_cast<int>(input.size());
        bondVec.reserve(InputLen);
        // 1. build each bitTabLe & move it into bondVec
        for (auto&& num : input) {
            bond temp;
            temp.val = num;
            //
            for (int tmp = num; tmp > 0; tmp /= InputLen) {
                temp.bitTable.push_back(tmp % InputLen);
            }
            if (static_cast<int>(temp.bitTable.size()) - 1 > highest_bit_POS) {
                highest_bit_POS = static_cast<int>(temp.bitTable.size()) - 1;
            }
            //
            bondVec.emplace_back(std::move(temp));
        }
        // 2. fill each bitTable
        for (auto&& uBond : bondVec) {
            int curr_highest_POS = static_cast<int>(uBond.bitTable.size()) - 1;
            for (; curr_highest_POS < highest_bit_POS; ++curr_highest_POS) {
                uBond.bitTable.push_back(0);
            }
        }
    };
    void DAA_Sort(int& KeyPOS, const int& ToSortLen) {
        // 0. init DAA
        DAA.reserve(ToSortLen);
        // initialize DAA => necessary
        std::vector<bond> init_elem {};
        for (int i = 0; i < ToSortLen; i++) {
            DAA.emplace_back(init_elem);
        }
        // 1. bondVec ==to==> DAA
        for (auto&& uBond : bondVec) {
            // int key = uBond.bitTable[KeyPOS];
            DAA[uBond.bitTable[KeyPOS]].push_back(uBond);
        }
        // 2. DAA == to==> bondVec
        int scannedNums = 0;
        for (auto&& bonds : DAA) {
            if (scannedNums == ToSortLen) {
                break;
            }
            if (bonds.size() == 0) {
                continue;
            }
            for (auto&& bond : bonds) {
                bondVec[scannedNums] = bond;
                scannedNums += 1;
            }
        }
        // 3. clear DAA => necessary
        DAA.erase(DAA.begin(), DAA.end());
    };
    void abstract_from_bondVec(vector<int>& output) {
        const int InputLen = static_cast<int>(output.size());
        int scannedNums    = 0;
        for (auto&& uBond : bondVec) {
            if (scannedNums == InputLen) {
                break;
            }
            output[scannedNums] = uBond.val;
            scannedNums += 1;
        }
    };
    void println_Vec(vector<int>& input) {
        for (auto&& num : input) {
            std::cout << num << " ";
        }
        cout << "\b \b";
        cout << endl;
    };

public:
    vector<int> generateVec() {
        vector<int> gen {};
        constexpr int length = 12;
        gen.reserve(length);
        srand(time(nullptr));
        function<int(const int&, const int&)> getPower
            = [](const int& x, const int& n) -> int {
            int res = 1;
            if (x == 2) {
                return 1 << n;
            }
            for (int i = 0; i < n; ++i) {
                res *= x;
            }
            return res;
        };
        for (int i = 0; i < length; ++i) {
            constexpr int max       = (length * length);
            const int MAX_DANGEROUS = getPower(length, length);
            constexpr int min       = 1;
            int tmp                 = (rand() % (MAX_DANGEROUS - min + 1)) + 1; // tmp in [min, max]
            gen.emplace_back(tmp);
        }
        return gen;
    }
    void assert_ifOrdered(vector<int>& inputVec) {
        // check if ascending-ordered here
        if (inputVec.empty() || inputVec.size() == 1) {
            return;
        }
        for (int i = 0; i < inputVec.size() - 1 - 1; i++) {
            assert(inputVec[i] <= inputVec[i + 1]);
        }
    }
    void interface(vector<int>& inputVec) {
        println_Vec(inputVec);
        solution(inputVec);
        println_Vec(inputVec);
        cout << endl;
        assert_ifOrdered(inputVec);
        cout << "Successfully Ordered the vector (ascending order). " << endl;
        cout << endl;
    };
    void solution(vector<int>& input) {
        static const int InputLen = static_cast<int>(input.size());
        // initialize bondVec
        init_bondVec(input);
        // DAA_Sort
        for (int i = 0; i <= highest_bit_POS; ++i) {
            DAA_Sort(i, InputLen);
        }
        // input <==pull== bondVec
        abstract_from_bondVec(input);
        // clean
        DAA.erase(DAA.begin(), DAA.end());
        bondVec.erase(bondVec.begin(), bondVec.end());
        DAA.shrink_to_fit();
        bondVec.shrink_to_fit();
        highest_bit_POS = -1;
    };
    static void example() {
        RadixSort TestObj;
        vector<int> vector_gen = TestObj.generateVec();
        vector<int> vector_def = { 1, 2, 4, 1, 6, 7, 5, 10, 9, 15, 30 };
        TestObj.interface(vector_gen);
        TestObj.interface(vector_def);
        cout << endl;
    }
};