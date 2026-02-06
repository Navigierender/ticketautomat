#ifndef MONEY_UTIL_H
#define MONEY_UTIL_H

#include <vector>

using namespace std;

/**
 * @brief Represents a reservoir of currency denominations.
 * @details The values represent the count of internal currency units: (v17: 17 units, v11: 11 units, v7: 7 units, v5: 5 units, v3: 3 units, v2: 2 units, v1: 1 unit)
 */
struct change {
    int v17;
    int v11;
    int v7;
    int v5;
    int v3;
    int v2;
    int v1;
};

namespace MoneyUtil {
    /**
     * @brief Determines if it's possible to give change for a given amount from the reservoir.
     * @param amount The amount for which to check if change can be provided.
     * @param reservoir The current money reservoir.
     * @return True if change can be provided, false otherwise.
     */
    bool changeOutPossible(int amount, change& reservoir);
    /**
     * @brief Processes the change output for a given amount, updating the reservoir.
     * @param amount The amount of change to process.
     * @param reservoir The money reservoir to be updated.
     * @return A 'change' struct representing the dispensed change.
     */
    change processChangeOut(int amount, change& reservoir);
    /**
     * @brief Converts a 'change' struct into a vector of integers representing currency counts.
     * @param c The 'change' struct to convert.
     * @return A vector of integers, where each element corresponds to the count of a specific currency denomination.
     */
    vector<int> changeToVector(const change& c);
}

#endif