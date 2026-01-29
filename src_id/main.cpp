#include "io.h"
#include "uiFormat.h"
#include "tramManager.h"
#include "monCalc.h"

#include <iostream>
#include <string>
#include <cmath> // For abs in getStationDistance, though moved to tramManager.cpp

using namespace std;

// Structure to hold information about the current route selection.
// This helps in passing related data around more easily.
struct route {
    TramLine* tram_ptr;         // Pointer to the selected tram line
    string start_station;       // Name of the start station
    string end_station;         // Name of the end station
    int price_direct;           // Calculated direct price for the journey
    change price_resolved;      // Not used in original code logic, but kept for replication
};

int main()
{
    // Initial money reservoir with custom denominations
    change money_reservoir = {2,2,2,2,2,2,2}; // Added `seventeen` denomination initialized to 2
    const int MINWIDTH = 42; // Minimum width for UI boxes
    const string SEP = Ui::repeatUTF8string(3,"\n"); // Separator for UI elements
    route c_route; // Current route details

    // Load tram line data from the specified directory
    vector<TramLine> tram_lines = TramManager::loadTrams("tram_data");

    // Extract tram numbers as strings for input validation
    vector<string> tram_num_strs;
    for (TramLine& t : tram_lines) { tram_num_strs.push_back(to_string(t.tram_number)); }

    // Main application loop
    while(true) {
        // Tram Line Selection
        cout << Ui::drawBox("Linienauswahl", tram_num_strs, MINWIDTH);
        int tram_number = stoi(Io::valInStrict("Eingabe", "Ungültige Eingabe", tram_num_strs));

        c_route.tram_ptr = TramManager::getTram(tram_lines, tram_number);
        vector<string> all_c_tram_stations = c_route.tram_ptr->stations;

        // Station Selection Loop
        while(true) {
            cout << SEP << Ui::drawBox("Startstation", all_c_tram_stations, MINWIDTH);
            c_route.start_station = Io::valInStrict("Eingabe", "Ungültige Eingabe", all_c_tram_stations);

            cout << SEP << Ui::drawBox("Endstation", all_c_tram_stations, MINWIDTH);
            c_route.end_station = Io::valInStrict("Eingabe", "Ungültige Eingabe", all_c_tram_stations);

            // Validate start and end stations are not the same
            if (c_route.start_station == c_route.end_station) { 
                cout << SEP << Ui::drawBox("Ungültige Reise",{"Ankunftshaltestelle und","Anreisehaltestelle","sind gleich!"},MINWIDTH); 
            } 
            else { 
                break; // Exit station selection loop if valid
            }
        }

        // Calculate fare
        c_route.price_direct = c_route.tram_ptr->price_per_station * TramManager::getStationDistance(c_route.tram_ptr, c_route.start_station, c_route.end_station);
        
        // Payment and Change Loop
        while (true) {
            cout << SEP << Ui::drawBox("Reiseinfo", {
                "Linie: " + to_string(c_route.tram_ptr->tram_number),
                "Start: " + c_route.start_station,
                "Ziel: " + c_route.end_station,
                "Preis: " + to_string(c_route.price_direct),
                Ui::repeatUTF8string(MINWIDTH-2,"-"),
                "zum abbrechen '0' eingeben"
            }, MINWIDTH);
            
            int money_input = Io::valUnder_oZERO("Belibiege Geld Eingabe", "Eingabe zu gering", c_route.price_direct);
            
            // Check if change can be returned or if transaction is cancelled (input 0)
            if (money_input == 0) { // User cancels transaction
                cout << SEP << Ui::drawBox("Transaktion abgebrochen", {"Kein Ticket gekauft."}, MINWIDTH);
                break; // Exit payment loop, return to main loop for new selection
            } else if (MoneyCalc::canReturnChange(money_input - c_route.price_direct, money_reservoir)) {
                // Calculate and dispense change, updating reservoir
                change money_output = MoneyCalc::calcChange(money_input, c_route.price_direct, money_reservoir);
                cout << SEP << Ui::drawBox("Rückgeld", Ui::changeToVec(money_output), MINWIDTH);
                break; // Exit payment loop, transaction complete
            } else {
                // Not enough change or invalid input
                cout << SEP << Ui::drawBox("Problem beim Rückgeld", {"Nicht genügend Wechselgeld vorhanden oder", "Eingabe unter dem Preis."}, MINWIDTH);
            }
        }
        
        // Option to terminate the program
        cout << SEP << Ui::drawBox("Programm beenden?", {"(0) Beenden", "(1) Weiter"}, MINWIDTH);
        if (Io::valInRange("Eingabe", "Ungültige Eingabe", 0, 1) == 0) break; // Exit main loop if user chooses to
    }

    return 0;
}
