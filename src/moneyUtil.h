#ifndef MONEY_UTIL_H
#define MONEY_UTIL_H

#include <vector>

/**
 * @brief Represents a reservoir of currency denominations
 * @details Values usually represent the count of {2e, 1e, 50c, 20c, 10c, 5c}
 */
struct change {
    int v17, v11, v7, v5, v3, v2, v1;
};

namespace MoneyCalc {
}

#endif