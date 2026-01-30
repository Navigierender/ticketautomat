#include "monCalc.h"
#include <cmath>

using namespace std;

change MoneyCalc::intToChange(int value) {
    change result = {0, 0, 0, 0, 0, 0, 0};
    if (value <= 0) return result;

    result.seventeen = value / 17; value %= 17;
    result.eleven    = value / 11; value %= 11;
    result.seven     = value / 7;  value %= 7;
    result.five      = value / 5;  value %= 5;
    result.three     = value / 3;  value %= 3;
    result.two       = value / 2;  value %= 2;
    result.one       = value;

    return result;
}

bool MoneyCalc::canReturnChange(int value, change reservoir) {
    if (value < 0) return false;
    if (value == 0) return true;
    
    value -= ((value / 17 < reservoir.seventeen) ? value / 17 : reservoir.seventeen) * 17;
    value -= ((value / 11 < reservoir.eleven)    ? value / 11 : reservoir.eleven)    * 11;
    value -= ((value / 7  < reservoir.seven)     ? value / 7  : reservoir.seven)     * 7;
    value -= ((value / 5  < reservoir.five)      ? value / 5  : reservoir.five)      * 5;
    value -= ((value / 3  < reservoir.three)     ? value / 3  : reservoir.three)     * 3;
    value -= ((value / 2  < reservoir.two)       ? value / 2  : reservoir.two)       * 2;
    value -= ((value / 1  < reservoir.one)       ? value / 1  : reservoir.one);

    return value == 0;
}

change MoneyCalc::calcChange(int paid, int price, change* reservoir) {
    int paid_cents  = static_cast<int>(round(paid * 100.0f));
    int price_cents = static_cast<int>(round(price * 100.0f));
    int diff_cents  = paid_cents - price_cents;

    change needed = intToChange(diff_cents);

    reservoir->seventeen -= needed.seventeen;
    reservoir->eleven    -= needed.eleven;
    reservoir->seven     -= needed.seven;
    reservoir->five      -= needed.five;
    reservoir->three     -= needed.three;
    reservoir->two       -= needed.two;
    reservoir->one       -= needed.one;
    
    return needed;
}