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

namespace intern {
    void drawPaymentMenu(const route& r, string title, string s0, string s1, string t_num, string p_msg, string c_msg, int width) {
        IoUtil::clearConsole();
        vector<string> lines = {
            t_num + ": " + to_string(r.tram_ptr->tram_number),
            s0 + ": " + r.stations[0],
            s1 + ": " + r.stations[1],
            p_msg + ": " + to_string(r.price),
            c_msg + " 0 eingeben"
        };
        cout << UiUtil::drawBox(title, lines, width);
    }

    void finishTransaction(string title, vector<string> lines, int width) {
        cout << UiUtil::drawBox(title, lines, width);
        IoUtil::awaitInput("Enter drücken um fortzufahren");
    }

    bool handleChangeLogic(int change_due, change& reservoir, string msg_out, int width) {
        if (!MoneyUtil::changeOutPossible(change_due, reservoir)) {
            finishTransaction("Fehler", {"Wechselgeld nicht verfügbar.", "Bitte anderen Betrag wählen."}, width);
            return false; // Transaction not finished, loop again
        }

        vector<string> display = {"Ticket wird ausgegeben...", ""};
        change c_out = MoneyUtil::processChangeOut(change_due, reservoir);
        vector<string> c_str = UiUtil::convertIntVecToStr(MoneyUtil::changeToVector(c_out));
        int denoms[] = {17, 11, 7, 5, 3, 2, 1};

        for (size_t i = 0; i < c_str.size(); ++i) {
            display.push_back(c_str[i] + "x " + to_string(denoms[i]));
        }
        finishTransaction(msg_out, display, width);
        return true; // Transaction finished
    }
}

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

    void finalizeOrSkip(const route& sel_route, change& reservoir, string msg_moneyout, string title, string msg_station0, string msg_station1, string msg_tram_number, string msg_price, string msg_cancel, int min_width) {
        while (true) {
            intern::drawPaymentMenu(sel_route, title, msg_station0, msg_station1, msg_tram_number, msg_price, msg_cancel, min_width);
            int money_input = IoUtil::valAboveOrZero("Geldeingabe", "Ungültige Geldmenge", sel_route.price);

            if (money_input == 0) return;

            int diff = money_input - sel_route.price;
            if (diff < 0) ErrLogger::stopAndLog(500, true);

            if (diff == 0) {
                intern::finishTransaction("Transaktion erfolgreich", {"Ticket wird ausgegeben..."}, min_width);
                return;
            }

            if (intern::handleChangeLogic(diff, reservoir, msg_moneyout, min_width)) return;
        }
    }
};
