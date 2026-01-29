#pragma once

#include <string>

/**
 * @brief Structure representing a collection of custom currency denominations.
 *        Each member stores the count of coins/units for its specific denomination.
 */
struct change {
    int seventeen, eleven, seven, five, three, two, one;
};

/**
 * @brief Provides functionality for monetary calculations, specifically
 *        dealing with custom change denominations and reservoir management.
 */
class MoneyCalc {
public:

    /**
     * @brief Converts a total cent value into the optimal distribution of custom change denominations.
     *        This function prioritizes larger denominations first.
     * @param value The total amount in cents to be converted.
     * @return A `change` struct containing the count of each custom coin denomination.
    **/
    static change intToChange(int value);

    /**
     * @brief Checks if a given amount can be returned as change using the available coins
     *        in a specified reservoir, considering the optimal distribution.
     * @param value The amount in cents to check if sufficient change exists for.
     * @param reservoir The current stock of available coins in each denomination.
     * @return `true` if the change can be returned, `false` otherwise (if any required coin
     *         denomination is insufficient in the reservoir).
    **/
    static bool canReturnChange(int value ,change reservoir);

    /**
     * @brief Calculates the change to be returned for a transaction and directly
     *        subtracts the returned coins from the provided money reservoir.
     * @param paid The amount paid by the user.
     * @param price The price of the item.
     * @param reservoir A reference to the `change` struct representing the money stock,
     *                  which will be modified by subtracting the returned change.
     * @return A `change` struct representing the exact coins that were returned to the user.
    **/
    static change calcChange(int paid, int price, change& reservoir);
};
