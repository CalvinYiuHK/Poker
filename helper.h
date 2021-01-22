//
// Created by Yiu Ka Wing on 21/1/2021.
//

#include <unordered_map>
#include <vector>
#include "compare.h"

#ifndef POKER_HELPER_H
#define POKER_HELPER_H


class helper {
public:
    static std::unordered_map<int, int> hand_counter(const compare::hand &hand1);
    static int find_value(std::unordered_map<int, int> counter, int target);
    static void split_hand(int tar_int, int tar_vec, int &hand_int, std::vector<int> &hand_vec, std::unordered_map<int, int> counter);
    static bool check_duplicate(const compare::hand &hand1);
};


#endif //POKER_HELPER_H
