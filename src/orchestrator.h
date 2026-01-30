#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#include "tramUtil.h"
#include "uiUtil.h"
#include "ioUtil.h"
#include "moneyUtil.h"
#include "tramUtil.h"

#include <vector>
#include <string>

using namespace std;

namespace Orst {
    const tramLine* reqTramSelec(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int width);

    vector<string> reqStationsSelect(const tramLine* tramline_ptr, int width);

    const int fetchRoutePrice(sel_route.tram_ptr, sel_route.stations);

    const bool reqContinue(string msg);

    const void finalizeOrSkip(route sel_route, string msg_tram_number, string msg_price, string msg_quit);
};

#endif