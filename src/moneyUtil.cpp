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

    change processChangeOut(int amount, change& reservoir) {
        change out = {0,0,0,0,0,0,0};
        int denoms[] = {17, 11, 7, 5, 3, 2, 1};
        int* counts[] = {&reservoir.v17, &reservoir.v11, &reservoir.v7, &reservoir.v5, &reservoir.v3, &reservoir.v2, &reservoir.v1};
        int* out_counts[] = {&out.v17, &out.v11, &out.v7, &out.v5, &out.v3, &out.v2, &out.v1};

        for (int i = 0; i < 7; i++) {
            while (amount >= denoms[i] && *counts[i] > 0) {
                amount -= denoms[i];
                (*counts[i])--;
                (*out_counts[i])++;
            }
        }

        return out;
    }

    vector<int> changeToVector(const change& c) {
        return {c.v17, c.v11, c.v7, c.v5, c.v3, c.v2, c.v1};
    }
}