//
// Created by Yiu Ka Wing on 21/1/2021.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <string>

#ifndef POKER_COMPARE_H
#define POKER_COMPARE_H


class compare {
public:
    typedef std::vector<std::tuple<int, int>> hand;
    static bool sorting_operator(std::tuple<int, int> i, std::tuple<int, int> j);
    static int compare_high_card(const hand &hand1 , const hand &hand2);
    static bool check_flush(const hand &hand1);
    static bool check_straight(const hand &hand1);
    static bool check_full_house(const hand &hand1);
    static bool check_four_of_a_kind(const hand &hand1);
    static int rank(const hand &hand1);
    static int compare_full_house(const hand &hand1 , const hand &hand2);
    static int compare_four_of_a_kind(const hand &hand1 , const hand &hand2);
    static int compare_three_of_a_kind(const hand &hand1 , const hand &hand2);
    static int compare_two_pairs(const hand &hand1 , const hand &hand2);
    static int compare_pair(const hand &hand1 , const hand &hand2);
    static int compare_same_rank(const hand &hand1 , const hand &hand2, int rank);
    static int compare_hand(hand &hand1, hand &hand2);
};


#endif //POKER_COMPARE_H
