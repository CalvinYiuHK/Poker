//
// Created by Yiu Ka Wing on 21/1/2021.
//

#include "helper.h"

std::unordered_map<int, int> helper::hand_counter(const compare::hand &hand1) {
    std::unordered_map<int, int> counter;

    for (int i = 0; i < 5; i++) {
        int number = std::get<0>(hand1.at(i));
        if (counter.find(number) != counter.end())
            counter[number]++;
        else
            counter[number] = 1;
    }
    return counter;
}

int helper::find_value(std::unordered_map<int, int> counter, int target) {
    for (auto& it:counter){
        if (it.second == target)
            return it.first;
    }
}

// split the hand into an int and a vector according to the requirement
void helper::split_hand(int tar_int, int tar_vec, int &hand_int, std::vector<int> &hand_vec, std::unordered_map<int, int> counter) {
    for (auto& it:counter){
        if (it.second == tar_int)
            hand_int = it.first;
        else if (it.second == tar_vec)
            hand_vec.push_back(it.first);
    }

    std::sort(hand_vec.begin(), hand_vec.end());

}

bool helper::check_duplicate(const compare::hand &hand1) {
    std::unordered_map<int, int> counter;
    for (int i = 0; i < 5; i++){
        std::tuple<int, int> card = hand1.at(i);
        // wont duplicate, 13 numbers and 4 suits
        int key = std::get<0>(card) * 4 + std::get<1>(card);
        if (counter.find(key) != counter.end())
            counter[key]++;
        else
            counter[key] = 1;
    }
    return counter.size() != 5;
}

