/**
 * @file Match_The_Same_Birthday.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief {
        0. pre_definations => struct birthday { int month; int day; };
        1. found those who have the same birthday
        2. return all <date:birthday, vector<name:string>> pairs
    }
 * @version 0.1
 * @date 2022-07-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

/**
 * @attention => only match the same day and same month, year is not considered
 */
class Match_The_Same_Birthday {
public:
    static inline void interface();

private:
    struct birthday { // visibility is public by default
        int month;
        int day;
        auto birthday_to_string() -> std::string {
            return std::to_string(month) + "." + std::to_string(day);
        }
    };
    using type_in  = std::unordered_map<std::string, birthday>;    // alias => input_type
    using type_res = std::map<birthday, std::vector<std::string>>; // alias => result_type
    static inline auto solution(type_in input) -> type_res;        // give the result
    static inline void print_output(type_res result);              // print the result
};

auto Match_The_Same_Birthday::solution(type_in input) -> type_res {
    type_res res;
    if (input.empty() || input.size() == 1) { // if input is empty or only one person
        return res;                           // then the result must be NONE
    }
    std::unordered_map<int, std::vector<std::string>> month_table;
    // fill the month_table
    for (const auto& _pair : input) {
        std::string _name  = _pair.first;
        birthday _birthday = _pair.second;
        month_table[_birthday.month].push_back(_name);
    }
    // search in each month
    for (const auto& _pair : month_table) {
        // generate vector to store whose birthdays have the same month
        std::vector<std::pair<std::string, birthday>> temp_container;
        // The reason to use vector<pair<>> instead of map<> =>
        // map<> has a double direction iterator,
        // which is not supported by gcc_sort method (it only supports one direction iterator).
        std::vector<std::string> _names = _pair.second;
        int _month                      = _pair.first;
        for (const auto& _name : _names) {
            birthday _birthday = input[_name];
            auto pair_to_push  = std::make_pair(_name, _birthday);
            temp_container.push_back(pair_to_push);
        }
        // sort the container
        std::sort(
            temp_container.begin(),
            temp_container.end(),
            [](
                const std::pair<std::string, birthday>& one,
                const std::pair<std::string, birthday>& another
            ) {
                return one.second.day < another.second.day;
            }
        );
        // search the same birthday
        for (int i = 0; i + 1 < temp_container.size(); i++) {
            if (temp_container[i].second.day == temp_container[i + 1].second.day) {
                res[temp_container[i].second]
                    .push_back(temp_container[i].first);
                res[temp_container[i].second]
                    .push_back(temp_container[i + 1].first);
            }
        }
    }
    // unique each vector in the result unordered_map
    for (auto& _pair : res) {
        std::sort(_pair.second.begin(), _pair.second.end());
        _pair.second.erase(
            std::unique(_pair.second.begin(), _pair.second.end()),
            _pair.second.end()
        );
    }
    // return the result
    return res;
}