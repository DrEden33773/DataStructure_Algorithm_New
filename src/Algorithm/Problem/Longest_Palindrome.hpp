#include <bits/stdc++.h>
using namespace std;

/**
 * @brief "babad" => "bab" or "aba"
 * @method DP
 */
class LongestPalindrome {
public:
    string longestPalindrome(string& s) {
        string res;

        /// <content>

        // special case #1
        if (s.length() == 1) {
            res = move(s);
            return res;
        }

        /// </content>

        return res;
    }
    static void example() {
        LongestPalindrome TestClass;
        string TestString = "babab";
        string Res        = TestClass.longestPalindrome(TestString);
        cout << endl;
        cout << "Input  : " << TestString << endl;
        cout << "Result : " << Res << endl;
        cout << endl;
    }
};