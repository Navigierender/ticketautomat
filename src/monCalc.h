#pragma once

#include <string>

struct change {
    int seventeen, eleven, seven, five, three, two, one;
};

class MoneyCalc {
public:
    static change intToChange(int value);
    bool MoneyCalc::canReturnChange(int value ,change reservoir);
    static change calcChange(int paid, int price, change* reservouir);
};