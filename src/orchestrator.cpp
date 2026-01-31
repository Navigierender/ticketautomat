#include "tramUtil.h"
#include "uiUtil.h"
#include "ioUtil.h"
#include "moneyUtil.h"
#include "tramUtil.h"
#include "errorHandler.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace Orst {
    void dependencyChecks() {
        IoUtil::dependencyCheck();
        UiUtil::dependencyCheck();
    }

    const tramLine* reqTramSelec(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int min_width) {
        IoUtil::clearConsole();
        cout << UiUtil::drawBox(title, UiUtil::convertIntVecToStr(valid_ids), min_width);
        int choice = IoUtil::intValInStrict("Eingabe", "Ungültige Nummer", valid_ids);
        return &TramUtil::getTram(all_trams, choice);
    }

    vector<string> reqStationsSelect(string title_stdec0, string title_stdec1, const tramLine* tramline_ptr, int min_width) {
        vector<string> tram_stations = tramline_ptr->stations;
        vector<string> choice_stdec;

        IoUtil::clearConsole();
        cout << UiUtil::drawBox(title_stdec0, tram_stations,min_width);
        choice_stdec.push_back(IoUtil::strValInStrict("Eingabe","Ungültige Eingabe",tram_stations));

        IoUtil::clearConsole();
        cout << UiUtil::drawBox(title_stdec1, tram_stations,min_width);
        choice_stdec.push_back(IoUtil::strValInStrict("Eingabe","Ungültige Eingabe",tram_stations));

        return choice_stdec;
    }

    int fetchRoutePrice(const tramLine* tram_ptr, const vector<string>& stations) {
        int station_distance = TramUtil::getStationDistance(tram_ptr, stations);
        return station_distance * tram_ptr->station_price;
    }

    bool reqContinue(string msg, int min_width) {
        IoUtil::clearConsole();
        cout << UiUtil::drawBox(msg,{("Automat beenden (q)"),("Automat nutzen (w)")},min_width);
        string state = IoUtil::strValInStrict("Eigabe","Ungültige Eingabe",{"q","w"});
        if (state == "q") return false;
        else return true;
    }

    void finalizeOrSkip(const route& sel_route,change& reservoir, string msg_moneyout, string title, string msg_station0, string msg_station1, string msg_tram_number, string msg_price, string msg_cancel, int min_width) {
        string trm_num = to_string(sel_route.tram_ptr->tram_number);
        string station0 = sel_route.stations[0];
        string station1 = sel_route.stations[1];
        string price_str = to_string(sel_route.price);

        while(true) {
            IoUtil::clearConsole();
            cout << UiUtil::drawBox(title,{(msg_tram_number+": "+trm_num),(msg_station0+": "+station0),(msg_station1+": "+station1),(msg_price+": "+price_str),(msg_cancel+" 0 eingeben")},min_width);

            int money_input = IoUtil::valAboveOrZero("Geldeingabe","Ungültige Geldmenge",sel_route.price);
            
            if (money_input == 0) return;

            int change_due = money_input - sel_route.price;

            if (change_due < 0) { 
                ErrLogger::stopAndLog(500,true);
            } else if (change_due == 0) {
                cout << UiUtil::drawBox("Transaktion erfolgreich",{"Ticket wird ausgegeben..."},min_width);
                IoUtil::awaitInput("Enter drücken um fortzufahren");
                return;
            } else {
                if (!MoneyUtil::changeOutPossible(change_due,reservoir)) {
                    cout << UiUtil::drawBox("Fehler",{"Wechselgeld nicht verfügbar. Bitte versuchen Sie es mit einem anderen Betrag."},min_width);
                    IoUtil::awaitInput("Enter drücken um fortzufahren");
                    continue;
                };
                change money_out_change = MoneyUtil::processChangeOut(change_due,reservoir);
                vector<string> money_out_str = UiUtil::convertIntVecToStr(MoneyUtil::changeToVector(money_out_change));
                cout << UiUtil::drawBox(msg_moneyout,{(money_out_str[0]+""),(money_out_str[1]+""),(money_out_str[2]+""),(money_out_str[3]+""),(money_out_str[4]+""),(money_out_str[5]+""),(money_out_str[6]+""),(money_out_str[7]+""),},min_width);
                IoUtil::awaitInput("Enter drücken um fortzufahren");
                return;
            }
        }
    }
};
