#pragma once

#include <string>

struct change {
    int fiveH_e;
    int twoH_e;
    int oneH_e;
    int fifty_e;
    int twenty_e;
    int ten_e;
    int five_e;
    int two_e;
    int one_e;
    int fifty_c;
    int twenty_c;
    int ten_c;
    int five_c;
    int two_c;
    int one_c;
};

class MoneyCalc {
public:
    static change intToChange(int cents);
    static std::string formatPrice(float price);
    static change calcChange(float paid, float price);
};
