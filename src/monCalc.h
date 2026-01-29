#pragma once

#include <string>

struct change {
    int eleven, seven, five, three, two, one;
};

class MoneyCalc {
public:
    static change intToChange(int value);
    static bool canReturnChange(int value ,change reservoir);
    static change calcChange(int paid, int price, change& reservouir);
};