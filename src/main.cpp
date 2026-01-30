#include "orchestrator.h"
#include "tramUtil.h"
#include "errorHandler.h"

#include <string>
#include <vector>

using namespace std;

ErrLogger::initErrList("errors");

const int MINWIDTH = 42;
const string SEP = UiUtil::repeatUTF8string(3,"\n");

const vector<tramLine> ALL_TRAMS= TramUtil::loadTrams("tram_data");
const vector<int> ALL_TRAMN_IDS = TramUtil::getTramINTs(ALL_TRAMS);

change money_reservoir = {2,2,2,2,2,2};

int main() {
    route sel_route;

    //main loop
    while (true) {
        Ui::resetUIaClean();

        if (Orst::reqContinue() == false) break;

        sel_route.tram_ptr = Orst::reqTramSelec(ALL_TRAMS, ALL_TRAMN_IDS, "Bahnauswahl", MINWIDTH);
        sel_route.stations = Orst::reqStationsSelect(sel_route.tram_ptr, MINWIDTH);
        sel_route.price = Orst::fetchRoutePrice(sel_route.tram_ptr, sel_route.stations);

        Orst::finalizeOrSkip(sel_route, "Linie", "Preis", "Zum Beenden");
    }

    return 0
}