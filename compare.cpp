//
// Created by Yiu Ka Wing on 21/1/2021.
//

#include <iostream>
#include "compare.h"
#include "helper.h"

// For all compare function: -1: draw, 0: hand2 > hand1, 1: hand1 > hand2

bool compare::sorting_operator(std::tuple<int, int> i, std::tuple<int, int> j) {
    return (std::get<0>(i) < std::get<0>(j) );
}

int compare::compare_high_card(const hand &hand1, const hand &hand2) {
    for (int i = 4; i >= 0 ; i-- ){
        if (std::get<0>(hand1.at(i)) != std::get<0>(hand2.at(i)))
            return std::get<0>(hand1.at(i)) > std::get<0>(hand2.at(i));
    }
    // same
    return -1;
}

bool compare::check_flush(const compare::hand &hand1) {
    int suit = std::get<1>(hand1.at(0));
    for (int i = 1; i < 5; i++){
        if (std::get<1>(hand1.at(i)) != suit)
            return false;
    }
    return true;
}

bool compare::check_straight(const compare::hand &hand1) {
    int last = std::get<0>(hand1.at(0));
    for (int i = 1; i < 5; i++){
        if (i == 4 && std::get<0>(hand1.at(4)) == 14 && std::get<0>(hand1.at(0)) == 2)
            return true;
        else if (std::get<0>(hand1.at(i)) == last + 1)
            last += 1;
        else
            return false;
    }
    return true;
}

bool compare::check_full_house(const compare::hand &hand1) {
    std::unordered_map<int, int> counter;

    for (int i = 0; i < 5; i++) {
        int number = std::get<0>(hand1.at(i));
        if (counter.find(number) != counter.end())
            counter[number]++;
        else
            counter[number] = 1;
    }

    if (counter.size() != 2){
        return false;
    }

    for (auto& it:counter){
        if (it.second != 2 && it.second != 3)
            return false;
    }
    return true;
}

bool compare::check_four_of_a_kind(const compare::hand &hand1) {
    std::unordered_map<int, int> counter;

    for (int i = 0; i < 5; i++) {
        int number = std::get<0>(hand1.at(i));
        if (counter.find(number) != counter.end())
            counter[number]++;
        else
            counter[number] = 1;
    }

    if (counter.size() != 2){
        return false;
    }

    for (auto& it:counter){
        if (it.second != 1 && it.second != 4)
            return false;
    }
    return true;
}

int compare::compare_full_house(const compare::hand &hand1, const compare::hand &hand2) {
    std::unordered_map<int, int> counter1 = helper::hand_counter(hand1);
    std::unordered_map<int, int> counter2 = helper::hand_counter(hand2);

    int hand1_d = helper::find_value(counter1, 2);
    int hand1_t = helper::find_value(counter1, 3);
    int hand2_d = helper::find_value(counter2, 2);
    int hand2_t = helper::find_value(counter2, 3);

    if (hand1_t == hand2_t){
        if (hand1_d == hand2_d)
            return -1;
        else
            return hand1_d > hand2_d;
    } else
        return hand1_t > hand2_t;
}

int compare::compare_four_of_a_kind(const compare::hand &hand1, const compare::hand &hand2) {
    std::unordered_map<int, int> counter1 = helper::hand_counter(hand1);
    std::unordered_map<int, int> counter2 = helper::hand_counter(hand2);

    int hand1_s = helper::find_value(counter1, 1);
    int hand1_q = helper::find_value(counter1, 4);
    int hand2_s = helper::find_value(counter2, 1);
    int hand2_q = helper::find_value(counter2, 4);

    if (hand1_q == hand2_q){
        if (hand1_s == hand2_s)
            return -1;
        else
            return hand1_s > hand2_s;
    } else
        return hand1_q > hand2_q;
}

int compare::rank(const compare::hand &hand1) {
    std::unordered_map<int, int> counter = helper::hand_counter(hand1);


    if (counter.size() == 5) {
        bool straight = check_straight(hand1);
        bool flush = check_flush(hand1);
        if (straight && flush)
            // straight flush
            return 1;
        else if (flush)
            // flush
            return 4;
        else if (straight)
            // straight
            return 5;
        else
            // high card
            return 9;
    } else if (counter.size() == 4){
        // pair
        return 8;
    } else if (counter.size() == 3){
        for (auto& it:counter){
            if (it.second == 3)
                // 3 of a kind
                return 6;
            else if (it.second == 2)
                // 2 pairs
                return 7;
        }
    } else if (counter.size() == 2){
        for (auto& it:counter){
            if (it.second == 4)
                // 4 of a kind
                return 2;
            else if (it.second == 2)
                // full house
                return 3;
        }
    }

    return -1;
}

int compare::compare_three_of_a_kind(const compare::hand &hand1, const compare::hand &hand2) {
    std::unordered_map<int, int> counter1 = helper::hand_counter(hand1);
    std::unordered_map<int, int> counter2 = helper::hand_counter(hand2);

    int hand1_t = helper::find_value(counter1, 3);
    int hand2_t = helper::find_value(counter2, 3);

    if (hand1_t != hand2_t)
        return hand1_t > hand2_t;

    int i1 = 4, i2 = 4;

    while (i1 >= 0 && i2 >= 0){
        int v1 = std::get<0>(hand1.at(i1));
        int v2 = std::get<0>(hand2.at(i2));
        if ( v1 == hand1_t){
            i1--;
            continue;
        } else if (v2 == hand2_t){
            i2--;
            continue;
        }

        if (v1 != v2)
            return v1 > v2;

        i1--;
        i2--;
    }
    return -1;
}

int compare::compare_two_pairs(const compare::hand &hand1, const compare::hand &hand2) {
    std::unordered_map<int, int> counter1 = helper::hand_counter(hand1);
    std::unordered_map<int, int> counter2 = helper::hand_counter(hand2);

    std::vector<int> hand1_d, hand2_d;
    int hand1_s, hand2_s;

    helper::split_hand(1, 2, hand1_s, hand1_d, counter1);
    helper::split_hand(1, 2, hand2_s, hand2_d, counter2);

    for (int i = 1; i >= 0; i--){
        if (hand1_d.at(i) != hand2_d.at(i))
            return hand1_d.at(i) > hand2_d.at(i);
    }
    if (hand1_s != hand2_s)
        return hand1_s > hand2_s;

    return -1;
}

int compare::compare_pair(const compare::hand &hand1, const compare::hand &hand2) {
    std::unordered_map<int, int> counter1 = helper::hand_counter(hand1);
    std::unordered_map<int, int> counter2 = helper::hand_counter(hand2);

    std::vector<int> hand1_s, hand2_s;
    int hand1_d, hand2_d;

    helper::split_hand(2, 1, hand1_d, hand1_s, counter1);
    helper::split_hand(2, 1, hand2_d, hand2_s, counter2);

    if (hand1_d != hand2_d)
        return hand1_d > hand2_d;

    for (int i = 2; i >= 0; i--){
        if (hand1_s.at(i) != hand2_s.at(i))
            return hand1_s.at(i) > hand2_s.at(i);
    }
    return -1;
}

int compare::compare_same_rank(const compare::hand &hand1, const compare::hand &hand2, int rank) {
    if (rank == 1 || rank == 4 || rank == 5 || rank == 9)
        // poker ignore suit
        return compare_high_card(hand1, hand2);
    else if (rank == 2)
        return compare_four_of_a_kind(hand1, hand2);
    else if (rank == 3)
        return compare_full_house(hand1, hand2);
    else if (rank == 6)
        return compare_three_of_a_kind(hand1, hand2);
    else if (rank == 7)
        return compare_two_pairs(hand1, hand2);
    else if (rank == 8)
        return compare_pair(hand1, hand2);
}

int compare::compare_hand(compare::hand &hand1, compare::hand &hand2) {
    std::string suits[] = {"♢", "♣", "♡", "♠"};

    if (helper::check_duplicate(hand1) || helper::check_duplicate(hand2)){
        std::cout << "Card duplicated.\n";
        exit(EXIT_FAILURE);
    }

    std::sort(hand1.begin(), hand1.end(), sorting_operator);
    std::sort(hand2.begin(), hand2.end(), sorting_operator);

    for (int hand = 1; hand < 3; hand++) {
        std::cout << "[Hand " << hand << "]\n";
        for (int i = 0; i < 5; i++) {
            std::tuple<int, int> card = (hand == 1)? hand1.at(i): hand2.at(i);
            int number = std::get<0>(card);
            int suit = std::get<1>(card);

            std::cout << suits[suit - 1];
            std::cout << ((number == 14)? "A": std::to_string(number)) << std::endl;
        }
    }

    int rank1 = rank(hand1);
    int rank2 = rank(hand2);

    if (rank1 == -1 || rank2 == -1){
        std::cout << "Wrong combination.\n";
        exit(EXIT_FAILURE);
    }

    if (rank1 != rank2)
        return rank1 < rank2;

    return compare_same_rank(hand1, hand2, rank1);
}


