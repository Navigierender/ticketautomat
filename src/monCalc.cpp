#include "monCalc.h"

#include <cmath>
#include <string>

using namespace std;

bool MoneyCalc::canReturnChange(int value, change reservoir) {
    change needed = intToChange(value);

    if (reservoir.eleven < needed.eleven) return false;
    if (reservoir.seven < needed.seven) return false;
    if (reservoir.five < needed.five) return false;
    if (reservoir.three < needed.three) return false;
    if (reservoir.two < needed.two) return false;
    if (reservoir.one < needed.one) return false;

    return true;
}

//converts cents to change struct
change MoneyCalc::intToChange(int value) {
    change result = {0,0,0,0,0,0}; // Initialize all members to 0
    int cents = value;

    result.eleven = cents / 11; cents %= 11;
    result.seven = cents / 7; cents %= 7;
    result.five = cents / 5; cents %= 5;
    result.three = cents / 3; cents %= 3;
    result.two = cents / 2; cents %= 2;
    result.one = cents;

    return result;
}

change MoneyCalc::calcChange(int paid, int price, change& reservoir) {
    int diff = paid - price;
    change change_to_return = intToChange(diff);

    reservoir.eleven -= change_to_return.eleven;
    reservoir.seven -= change_to_return.seven;
    reservoir.five -= change_to_return.five;
    reservoir.three -= change_to_return.three;
    reservoir.two -= change_to_return.two;
    reservoir.one -= change_to_return.one;

    return change_to_return;
}