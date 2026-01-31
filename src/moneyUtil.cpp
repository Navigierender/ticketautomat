#include "moneyUtil.h"

using namespace std;

namespace MoneyUtil {
    bool changeOutPossible(int amount, change& reservoir) {
        int denoms[] = {17, 11, 7, 5, 3, 2, 1};
        int counts[] = {reservoir.v17, reservoir.v11, reservoir.v7, reservoir.v5, reservoir.v3, reservoir.v2, reservoir.v1};

        for (int i = 0; i < 7; i++) {
            while (amount >= denoms[i] && counts[i] > 0) {
                amount -= denoms[i];
                counts[i]--;
            }
        }

        return (amount == 0);
    }
}