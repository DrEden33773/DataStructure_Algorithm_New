#include <bits/stdc++.h>
using namespace std;

class Sum_of_Three_Num {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        // construct
        vector<vector<int>> res;

        // special cases
        if (nums.empty()) {
            // empty
            return res;
        }
        if (*(nums.begin()) > 0 || *(nums.end()) < 0) {
            // too big/small
            return res;
        }

        // sort
        sort(nums.begin(), nums.end()); // ascending order

        // iterate
        size_t last = nums.size() - 1;
        map<pair<int, int>, bool> notation_of_tuple; // pair<int, int> <=> pair<first_num, second_num>
        map<int, bool> notation_of_first_num;
        for (int first = 0; first < nums.size() - 2; ++first) {
            if (nums[first] > 0) {
                // nums[first] is too big
                break;
            }
            // smallest + biggest + second_biggest < 0
            if (nums[first] + nums[last] + nums[last - 1] < 0) {
                // nums[first] is too small
                continue;
            } else {
                if (notation_of_first_num[nums[first]] == false) {
                    notation_of_first_num[nums[first]] = true;
                } else {
                    // nums[first] is duplicate
                    continue;
                }
                for (int second = first + 1; second < nums.size() - 1; ++second) {
                    vector<int> inner;
                    int sum_of_two = nums[first] + nums[second];
                    if (sum_of_two + nums[last] < 0) {
                        // sum_of_two is too small => the second is too small
                        // try to find a bigger `second`
                        continue;
                    }
                    if (sum_of_two > 0) { // >= is wrong, such as { 0, 0, 0 }
                        // sum_of_two is too big
                        // could not refind a smaller `second` => abort `first` and `second`
                        break;
                    }
                    // start to find!
                    int first_in_nums       = nums[first];
                    int second_in_nums      = nums[second];
                    auto find_third_element = [&first_in_nums, &second_in_nums](int i) {
                        return first_in_nums + second_in_nums + i == 0;
                    };
                    // give a iterator which points to nums[second + 1]
                    auto second_plus_one_iterator = nums.begin();
                    // ranges::advance(second_plus_one_iterator, second + 1);
                    for (int i = 0; i < second + 1; ++i) {
                        ++second_plus_one_iterator;
                    }
                    // find
                    auto the_third_element = find_if(
                        second_plus_one_iterator,
                        nums.end(),
                        find_third_element
                    );
                    if (the_third_element != nums.end()) {
                        // successfully find
                        // but need to make sure tuple<first_num, second_num> is unique

                        // make pair
                        auto curr_tuple_of_first_second = make_pair(first_in_nums, second_in_nums);
                        // check if the pair is already in the notation_of_tuple
                        if (notation_of_tuple[curr_tuple_of_first_second] == false) {
                            // not in the notation_of_tuple
                            notation_of_tuple[curr_tuple_of_first_second] = true;
                            // add to res
                            inner.push_back(first_in_nums);
                            inner.push_back(second_in_nums);
                            inner.push_back(*the_third_element);
                            res.push_back(inner);
                        } else {
                            // in the notation_of_tuple
                            continue;
                        }
                    }
                }
            }
        }

        // have to unique the res => now this is unnecessary
        // EG: {{-1,-1,2},{-1,0,1},{-1,0,1}} => {{-1,-1,2},{-1,0,1}}

        // auto Judge_Tuple_Equality =
        //     [&](vector<int>& InputA, vector<int>& InputB)
        //     -> bool {
        //     // {-1 -1 2} and {-1 2 -1}
        //     if (InputA.size() != InputB.size()) {
        //         return false;
        //     }
        //     sort(InputA.begin(), InputA.end());
        //     sort(InputB.begin(), InputB.end());
        //     bool res = true;
        //     for (int i = 0; i < InputA.size(); ++i) {
        //         if (InputA[i] != InputB[i]) {
        //             res = false;
        //             break;
        //         }
        //     }
        //     return res;
        // };
        // auto LAST = unique(res.begin(), res.end(), Judge_Tuple_Equality);
        // res.erase(LAST, res.end());

        return res;
    }

    static void example() {
        unique_ptr<Sum_of_Three_Num> TestSolution = make_unique<Sum_of_Three_Num>();
        // [-1,0,1,2,-1,-4]
        vector<int> TestVec
            = { -1, 0, 1, 2, -1, -4 }; // after sort => { -4, -1, -1, 0, 1, 2 }
        auto Result
            = TestSolution->threeSum(TestVec);
        // Print the outcome
        cout << endl;
        cout << "{";
        for (const auto& Tuple : Result) {
            cout << "{";
            for (const auto& Element : Tuple) {
                cout << Element << ",";
            }
            cout << "\b \b";
            cout << "},";
        }
        cout << "\b \b";
        cout << "}";
        cout << endl;
        cout << endl;
    }
};
