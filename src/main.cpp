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

change money_reservoir = {2,2,2,2,2,2,2};

int main() {
    #ifdef _WIN32
        ErrLogger::stopAndLog(600,true); //error 600 - wrong os
    #endif

    ErrLogger::initErrList("errors/errlist.err"); //trys to initialize errorlist from errors directory
    Orst::dependencyChecks();
    
    // Moved from global scope to ensure ErrLogger::initErrList is called first
    const vector<tramLine> ALL_TRAMS = TramUtil::loadTrams("tram_data");
    const vector<int> ALL_TRAMN_IDS = TramUtil::getTramINTs(&ALL_TRAMS);
    
    route sel_route;

    //main loop
    while (true) {
        IoUtil::clearConsole();

        if (Orst::reqContinue("Automat schliessen?",MINWIDTH) == false) break;

        sel_route.tram_ptr = Orst::reqTramSelec(ALL_TRAMS, ALL_TRAMN_IDS, "Bahnauswahl", MINWIDTH);
        sel_route.stations = Orst::reqStationsSelect("Startstation","Endstation", sel_route.tram_ptr, MINWIDTH);
        sel_route.price = Orst::fetchRoutePrice(sel_route.tram_ptr, sel_route.stations);

        Orst::finalizeOrSkip(sel_route, money_reservoir, "Rückgeld", "Reiseübersicht","Abreiseort","Ankunftsort","Linie","Preis","Zum Abbrechen",MINWIDTH);
    }

    return 0;
}
