#include "orchestrator.h"
#include "tramUtil.h"
#include "uiUtil.h"
#include "ioUtil.h"
#include "errorHandler.h"

#include <string>
#include <vector>

using namespace std;

const int MINWIDTH = 42;
const string SEP = UiUtil::repeatUTF8string(3,"\n");

const vector<tramLine> ALL_TRAMS = TramUtil::loadTrams("tram_data");
const vector<int> ALL_TRAMN_IDS = TramUtil::getTramINTs(ALL_TRAMS*);

change money_reservoir = {2,2,2,2,2,2};

int main() {
    #ifdef _WIN32
        ErrLogger::stopAndLog(600,false); //error 600 - wrong os
    #endif

    ErrLogger::initErrList("errors/errlist.err"); //trys to initialize errorlist from errors directory
    Orst::dependencyChecks();
    
    route sel_route;

    //main loop
    while (true) {
        IoUtil::clearConsole();

        if (Orst::reqContinue("Automat schliessen?") == false) break;

        sel_route.tram_ptr = Orst::reqTramSelec(ALL_TRAMS, ALL_TRAMN_IDS, "Bahnauswahl", MINWIDTH);
        sel_route.stations = Orst::reqStationsSelect(sel_route.tram_ptr, MINWIDTH);
        sel_route.price = Orst::fetchRoutePrice(sel_route.tram_ptr, sel_route.stations);

        Orst::finalizeOrSkip(sel_route, "Linie", "Preis", "Zum Beenden");
    }

    return 0
};