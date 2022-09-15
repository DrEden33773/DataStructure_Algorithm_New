/**
 * @file ColumnMatch.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Judge input sets of columns' correctness
 * @version 0.1
 * @date 2022-08-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

class ColumnMatch {
public:
    bool isValid(string& s) {
        bool res = false;

        // <  content  >

        if (s.empty() || s.size() % 2 != 0) {
            return false;
        }

        stack<char> TempStack   = {};
        bool _ifAnyMatchFailed_ = false;

        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                TempStack.push(c);
            } else {
                char currChar = TempStack.empty() ? '*' : TempStack.top();

                bool _smallColumnMatch_  = c == ')' && currChar == '(';
                bool _mediumColumnMatch_ = c == ']' && currChar == '[';
                bool _bigColumnMatch_    = c == '}' && currChar == '{';

                bool _ifCouldMatchThisTime_
                    = _smallColumnMatch_ || _mediumColumnMatch_ || _bigColumnMatch_;

                if (_ifCouldMatchThisTime_) {
                    TempStack.pop();
                } else {
                    res                = false;
                    _ifAnyMatchFailed_ = true;
                    break;
                }
            }
        }

        if (_ifAnyMatchFailed_) {
            res = false;
        } else {
            if (TempStack.empty()) {
                res = true;
            } else {
                res = false;
            }
        }

        // </ content />

        return res;
    }

    static void example() {
        string input = "}[";
        ColumnMatch Test;
        bool res = Test.isValid(input);
        cout << (res ? "true" : "false") << endl;
    }
};