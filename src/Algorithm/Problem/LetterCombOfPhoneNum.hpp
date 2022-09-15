/**
 * @file LetterCombOfPhoneNum.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
        Given a string containing digits from 2-9 inclusive,
        return all possible letter combinations that the number could represent.

        Return the answer in any order.

        A mapping of digits to letters (just like on the telephone buttons) is given below.
        Note that 1 does not map to any letters.

 * @version 0.1
 * @date 2022-08-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

class LetterCombOfPhoneNum {
public:
    vector<string> letterCombinations(string& digits) {
        vector<string> res {};

        if (digits.empty()) {
            res.emplace_back("");
            return res;
        }

        unordered_map<char, string> AllCombinations = {
            // { '0', "" },
            // { '1', "" },
            { '2', "abc" },
            { '3', "def" },
            { '4', "ghi" },
            { '5', "jkl" },
            { '6', "mno" },
            { '7', "pqrs" },
            { '8', "tuv" },
            { '9', "wxyz" }
        };

        if (digits.size() == 1) {
            for (char c : digits) {
                string tmp;
                tmp.push_back(c);
                res.push_back(tmp);
            }
            return res;
        }

        vector<string> TmpCombVec = {};
        for (char c : digits) {
            TmpCombVec.push_back(AllCombinations[c]);
        }

        return res;
    }
};