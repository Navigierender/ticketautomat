#include "orchestrator.h"
#include "UiUtils.h"
#include "ioUtils.h"
#include "tramManag.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MINDWIDTH = 42;
const string SEP = UI::repeatUTF8string(3,"\n");

const vector<tramLine> ALL_TRAMS= TramManag::loadTrams("tram_data");
const vector<int> ALL_TRAMN_IDS = TramManag::getTramINTs(ALL_TRAMS);

change money_reservoir = {2,2,2,2,2,2};

int main() {
    route sel_route;

    //main loop
    while (true) {
        UI::resetUIaClean();

        sel_route.tram_ptr = Orst::reqTramSelec(ALL_TRAMS, ALL_TRAMN_IDS, MINWIDTH);
        sel_route.stations = Orst::reqTramStationsSelec(sel_route.tram_ptr, MINDWIDTH);


    }

    return 0
}