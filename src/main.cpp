#include "io.h"
#include "uiFormat.h"
#include "tramManager.h"
#include "monCalc.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct route {
    TramLine* tram_ptr;
    string start_station;
    string end_station;
    int price_direct;
    change price_resolved;
};

int main()
{
    change money_reservoir = {2,2,2,2,2,2};
    const int MINWIDTH = 42;
    const string SEP = Ui::repeatUTF8string(3,"\n");
    route c_route;

    vector<TramLine> tram_lines = TramManager::loadTrams("tram_data");

    vector<string> tram_num_strs;
    for (TramLine& t : tram_lines) { tram_num_strs.push_back(to_string(t.tram_number)); }

    while(true) {
        cout << Ui::drawBox("Linienauswahl", tram_num_strs, MINWIDTH);
        int tram_number = stoi(Io::valInStrict("Eingabe", "Ungültige Eingabe", tram_num_strs));

        c_route.tram_ptr = TramManager::getTram(tram_lines, tram_number);
        vector<string> all_c_tram_stations = c_route.tram_ptr->stations;

        while(true) {
            cout << SEP << Ui::drawBox("Startstation", all_c_tram_stations, MINWIDTH);
            c_route.start_station = Io::valInStrict("Eingabe", "Ungültige Eingabe", all_c_tram_stations);

            cout << SEP << Ui::drawBox("Endstation", all_c_tram_stations, MINWIDTH);
            c_route.end_station = Io::valInStrict("Eingabe", "Ungültige Eingabe", all_c_tram_stations);

            if (c_route.start_station == c_route.end_station) { cout << SEP << Ui::drawBox("Ungültige Reise",{"Ankunftshaltestelle und","Anreisehaltestelle","sind gleich!"},MINWIDTH); }
            else { break; }
        }

        c_route.price_direct = c_route.tram_ptr->price_per_station * TramManager::getStationDistance(c_route.tram_ptr, c_route.start_station, c_route.end_station);
        
        while (true) {
            cout << SEP << Ui::drawBox("Reiseinfo", {"Linie: " + to_string(c_route.tram_ptr->tram_number),"Start: " + c_route.start_station,"Ziel: " + c_route.end_station,"Preis: " + to_string(c_route.price_direct),Ui::repeatUTF8string(MINWIDTH-2,"-"),"zum abbrechen '0' eingeben"}, MINWIDTH);
            int money_input = Io::valUnder_oZERO("Belibiege Geld Eingabe", "Eingabe zu gering", c_route.price_direct);
            if (MoneyCalc::canReturnChange(money_input,money_reservoir) || money_input == 0) {
                change money_output = MoneyCalc::calcChange(money_input,c_route.price_direct,money_reservoir*);
                cout << SEP << Ui::drawBox("Rückgeld", Ui::changeToVec(money_output), MINWIDTH);
                break;
            }
        }
    }

    return 0;
}