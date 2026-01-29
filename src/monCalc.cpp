#include "monCalc.h"

#include <cmath>
#include <string>

using namespace std;

//converts cents to change struct
change MoneyCalc::intToChange(int value) {
    change result = {0};

    result.fiveH_e = cents/50000; cents %= 50000;
    result.twoH_e = cents/20000; cents %= 20000;
    result.oneH_e = cents/10000; cents %= 10000;
    result.fifty_e = cents/5000; cents %= 5000;
    result.twenty_e = cents/2000; cents %= 2000;
    result.ten_e = cents/1000; cents %= 1000;
    result.five_e = cents/500; cents %= 500;
    result.two_e = cents/200; cents %= 200;
    result.one_e = cents/100; cents %= 100;
    result.fifty_c = cents/50; cents %= 50;
    result.twenty_c = cents/20; cents %= 20;
    result.ten_c = cents/10; cents %= 10;
    result.five_c = cents/5; cents %= 5;
    result.two_c = cents/2; cents %= 2;
    result.one_c = cents;

    return result;
}

change MoneyCalc::calcChange(int paid, int price, change reservoir) {
    int paid_cents  = static_cast<int>(round(paid * 100.0f));
    int price_cents = static_cast<int>(round(price * 100.0f));

    int diff_cents = paid_cents - price_cents;

    return intToChange(diff_cents);
}