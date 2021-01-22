#include <iostream>
#include <compare>
#include <vector>
#include <functional>
#include <map>
#include "compare.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "testing" << std::endl;

    compare::hand hand1;
    compare::hand hand2;

    for (int hand = 1; hand < 3; hand++) {
        for (int i = 1; i < 6; i++) {
            int number, suit;
            while ((std::cout << "[Hand " << hand << " Card " << i << "] Enter a number(1-13): " &&
                   !(std::cin >> number)) || number > 13 || number < 1) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                std::cout << "Invalid input; please re-enter.\n";
            }

            while ((std::cout << "[Hand " << hand << " Card " << i << "] Enter a suit (1-4): " &&
                    !(std::cin >> suit)) || suit > 4 || suit < 1) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                std::cout << "Invalid input; please re-enter.\n";
            }
            if (number == 1)
                number = 14;

            if (hand == 1)
                hand1.push_back(std::make_tuple(number, suit));
            else
                hand2.push_back(std::make_tuple(number, suit));
        }

    }

    int result = compare::compare_hand(hand1, hand2);

    std::cout << (result? "Hand 1 win.":  (result == 0)? "Hand 2 win.": "Draw." )<< '\n';

    return 0;
}
