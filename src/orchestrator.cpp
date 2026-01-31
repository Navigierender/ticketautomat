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

    const tramLine* reqTramSelect(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int min_width) {
        
        cout << UiUtil::drawBox(title, UiUtil::convertIntVecToStr(valid_ids), min_width);
        int choice = IoUtil::intValInStrict("Eingabe", "Ungültige Bahn Nummer", valid_ids);
        return &TramUtil::getTram(all_trams, choice);
    }

    vector<string> reqStationsSelect(string title_stdec0, string title_stdec1, const tramLine* tramline_ptr, int min_width) {
        vector<string> tram_stations = tramline_ptr->stations;
        vector<string> choice_stdec;

        cout << UiUtil::drawBox(title_stdec0, tram_stations,min_width);
        choice_stdec.push_back(IoUtil::strValInStrict("Eingabe","Ungültige Eingabe",tram_stations));

        cout << UiUtil::drawBox(title_stdec1, tram_stations,min_width);
        choice_stdec.push_back(IoUtil::strValInStrict("Eingabe","Ungültige Eingabe",tram_stations));

        return choice_stdec;
    }

    int fetchRoutePrice(const tramLine* tram_ptr, const vector<string> stations) {
        int station_distance = TramUtil::getStationDistance(tram_ptr, stations);
        return station_distance * tram_ptr->station_price;
    }

    bool reqContinue(string msg) {}

    void finalizeOrSkip(const route& sel_route, string msg_tram_number, string msg_price, string msg_quit) {}
};