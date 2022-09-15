/**
 * @file Transition_Of_Num_And_String.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 *      Give you a DEX number, and try to translate it into a string,
 *      the rule of which could be implied by the examples bellow:
 *      1 => A, 2 => B, 26 => Z, 27 => AA, 28 => AB, 52 => AZ, 53 => BA
 *      You also need to imply a method(function) to make "string => DEX number" possible
 *      An example will be "void itos(int& num)" and "void stoi(string& str)"
 * @version 0.1
 * @date 2022-09-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Transition_Of_Num_And_String {
    /**
     * @brief
     *  1 <=> A, 2 <=> B, 26 <=> Z, 27 <=> AA, 28 <=> AB, 52 <=> AZ, 53 <=> BA
     *  52 = 26 + 26
     */
public:
    static void example() {
        cout << endl;
        Transition_Of_Num_And_String testExample;
        int testInt    = 17576;
        string testStr = "YYZ";
        cout << testInt << " to " << testExample.itos(testInt) << endl;
        cout << testStr << " to " << testExample.stoi(testStr) << endl;
        cout << endl;
        cout << "now generate a random number between 1 and 999999" << endl;
        // generate a random number between 1 and 999999
        srand(time(nullptr));
        int randomNum = rand() % 999999 + 1;
        cout << "generated num => " << randomNum << endl;
        // judge
        string randomNum_itos   = testExample.itos(randomNum);
        int randomNum_itos_stoi = testExample.stoi(randomNum_itos);
        cout << randomNum << " to " << randomNum_itos << endl;
        cout << randomNum_itos << " to " << randomNum_itos_stoi << endl;
        assert(randomNum == randomNum_itos_stoi);
        cout << endl;
        cout << "successfully proved to be correct!" << endl;
        cout << endl;
    }
    string itos(int& num) {
        assert(num >= 0); // num >= 0
        string result = "";
        unordered_map<int, char> NumCharMap; // 构建hashmap
        NumCharMap[0] = '!';                 // error check signature
        // 初始化hashmap
        for (int i = 0; i < 26; ++i) {
            char currChar       = 'A' + i;
            int currNum         = 1 + i;
            NumCharMap[currNum] = currChar;
        }
        vector<int> BitTable; // 构建位数表
        // 初始化位数表 (现在只能得到反序表，稍后需要反转)
        for (int input = num; input > 0;) {
            // 这里面有一个很重要的细节！由于不存在0到A~Z的映射，所以遇到整除26的情况，需要反向借位
            int currRemainder   = input % 26;
            bool ifZeroOccurred = currRemainder == 0;
            if (!ifZeroOccurred) {
                BitTable.push_back(currRemainder);
                input /= 26;
            } else {
                BitTable.push_back(26); // 反向借位，26是“进制”值
                input /= 26;
                input -= 1; // 反向借位
            }
        }
        // 翻转位数表
        for (int i = 0; i <= (BitTable.size() - 1) / 2; ++i) {
            swap(BitTable[i], BitTable[BitTable.size() - 1 - i]);
        }
        // 填充结果
        for (auto element : BitTable) {
            result += NumCharMap[element];
        }
        return result;
    }
    int stoi(string& str) {
        int result = 0;
        unordered_map<char, int> CharNumMap; // 构建hashmap
        // 初始化hashmap
        for (int i = 0; i < 26; ++i) {
            char currChar        = 'A' + i;
            int currNum          = 1 + i;
            CharNumMap[currChar] = currNum;
        }
        // 求幂函数
        auto getPower = [](const int& input, const int& power) -> int {
            if (input == 2) {
                return 1 << power;
            }
            int res = 1;
            for (int i = power; i > 0; --i) {
                res *= input;
            }
            return res;
        };
        // 遍历字符串(一定是反方向，从右到左遍历)
        const size_t len = str.length();
        for (int i = len - 1, POS = 0; i >= 0; i--, ++POS) {
            const int currNumber = getPower(26, POS) * CharNumMap[str[i]];
            result += currNumber;
        }
        return result;
    }
};
