#include "tramUtil.h"
#include "uiUtil.h"
#include "ioUtil.h"
#include "moneyUtil.h"
#include "tramUtil.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace Orst {
    void dependencyCheck() {
        IoUtil::dependencyCheck();
        UiUtil::dependencyCheck();
    }

    const tramLine* reqTramSelect(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int width) {
        
        cout << UiUtil::drawBox(title, UiUtil::convertIntVecToStr(valid_ids), width);
        int choice = IoUtil::intValInStrict("Eingabe ID", "Ungültige ID!", valid_ids);
        return &TramUtil::getTram(all_trams, choice);
    }

    vector<string> reqStationsSelect(const tramLine* tramline_ptr, int width) {};

    int fetchRoutePrice(const tramLine* tram_ptr, const vector<string>& stations) {};

    bool reqContinue(string msg) {};

    void finalizeOrSkip(const route& sel_route, string msg_tram_number, string msg_price, string msg_quit) {};
};