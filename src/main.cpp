#include "io.hpp"
#include "uiFormat.hpp"
#include "tramManager.hpp"
#include "monCalc.hpp"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct route {
    TramLine* tram_ptr;
    string start_station;
    string end_station;
    float price_direct;
    change price_resolved;
};

int main()
{
    const int MINWIDTH = 42;
    const string SEPERATION = Ui::repeatUTF8string(3,"\n");
    route c_route;

    vector<TramLine> tram_lines = TramManager::loadTrams("C:/Users/Jaros/OneDrive/Studium/Module/GdP/Abschlussarbeit/21_ticketautomat/sftw_1/tram_data");
    vector<string> tram_num_strs;
    for (TramLine& t : tram_lines) { tram_num_strs.push_back(to_string(t.tram_number)); }

    cout << Ui::drawBox("Linienauswahl", tram_num_strs, MINWIDTH);
    int tram_number = stoi(Io::valInStrict("Eingabe", "Ungültige Eingabe", tram_num_strs));

    c_route.tram_ptr = TramManager::getTram(tram_lines, tram_number);
    vector<string> all_c_tram_stations = c_route.tram_ptr->stations;

    cout << SEPERATION << Ui::drawBox("Startstation", all_c_tram_stations, MINWIDTH);
    c_route.start_station = Io::valInStrict("Eingabe", "Ungültige Eingabe", all_c_tram_stations);

    cout << SEPERATION << Ui::drawBox("Endstation", all_c_tram_stations, MINWIDTH);
    c_route.end_station = Io::valInStrict("Eingabe", "Ungültige Eingabe", all_c_tram_stations);

    if (c_route.start_station == c_route.end_station) {
        cout << SEPERATION << Ui::drawBox("Ungültige Reise",{"Ankunftshaltestelle und","Anreisehaltestelle","sind gleich!"},MINWIDTH);
        return -1;
    }

    float raw_price = c_route.tram_ptr->price_per_station * TramManager::getStationDistance(c_route.tram_ptr, c_route.start_station, c_route.end_station);
    c_route.price_direct = round(raw_price * 100.0f) / 100.0f;

    cout << SEPERATION << Ui::drawBox("Reiseinfo", {"Linie: " + to_string(c_route.tram_ptr->tram_number),"Start: " + c_route.start_station,"Ziel: " + c_route.end_station,"Preis: " + MoneyCalc::formatPrice(c_route.price_direct)}, MINWIDTH);

    float money_input = Io::valAbove("Belibiege Geld Eingabe", "Eingabe zu gering", c_route.price_direct);

    change money_output = MoneyCalc::calcChange(money_input, c_route.price_direct);

    cout << SEPERATION << Ui::drawBox("Rückgeld", Ui::changeToVec(money_output), MINWIDTH);

    return 0;
}