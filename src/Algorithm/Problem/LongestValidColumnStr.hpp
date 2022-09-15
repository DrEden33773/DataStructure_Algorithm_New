/**
 * @file LongestValidColumnStr.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
            Given a string containing just the characters '(' and ')',
            find the length of the longest valid (well-formed) parentheses substring.
 *
 * @version 0.1
 * @date 2022-08-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

class LongestValidColumnStr {
public:
    int longestValidParentheses(string& s) {
        int res = 0;

        if (s.empty()) {
            return res;
        }

        vector<int> AllValidLen = {};
        stack<char> TempStack   = {};
        int CurrValidLen        = 0;

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
                    CurrValidLen += 2;
                    TempStack.pop();
                } else {
                    AllValidLen.push_back(CurrValidLen);
                    CurrValidLen = 0;
                    while (!TempStack.empty()) {
                        TempStack.pop();
                    }
                }
            }
        }

        AllValidLen.push_back(CurrValidLen); // If could match from s[n] to s[end - 1], then this will be useful

        sort(AllValidLen.begin(), AllValidLen.end());

        res = AllValidLen[AllValidLen.size() - 1];

        return res;
    }

    static void example() {
        LongestValidColumnStr Test;
        string Input = "()(()";
        int Res      = Test.longestValidParentheses(Input);
        cout << endl;
        cout << Input << " => " << Res << endl;
        cout << endl;
    }
};