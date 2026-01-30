#pragma once

#include <string>

/**
 * @brief stores the count of coins for each denomination
**/
struct change {
    int seventeen, eleven, seven, five, three, two, one;
};

class MoneyCalc {
public:

    /**
     * @brief converts a cent value into the ideal change distribution
     * @param value the total amount in cents to be converted
     * @return change struct containing the ideal number of each coin
    **/
    static change intToChange(int value);

    /**
     * @brief checks if a value can be represented using the available coins in the reservoir
     * @param value the amount in cents to check
     * @param reservoir the current stock of coins
     * @return true if the value can be changed, false if coins are missing
    **/
    static bool canReturnChange(int value ,change reservoir);

    /**
     * @brief calculates change and subtracts it directly from the given reservoir pointer
     * @param paid amount paid by the user
     * @param price price of the item
     * @param reservoir pointer to the stock that will be modified
     * @return change struct containing the coins removed from the reservoir
    **/
    static change calcChange(int paid, int price, change* reservoir);
};