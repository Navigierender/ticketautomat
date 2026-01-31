#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#include "tramUtil.h"
#include "uiUtil.h"
#include "moneyUtil.h"
#include "tramUtil.h"

#include <vector>
#include <string>

using namespace std;

namespace Orst {
    /**
     * @brief Performs initial dependency checks for the orchestrator, ensuring all required utilities are available.
     *        If a dependency is missing, it logs a critical error and terminates the program.
     */
    void dependencyChecks();

    /**
     * @brief Requests user to select a tram line
     * @param all_trams vector of all available tram lines
     * @param valid_ids vector of valid tram IDs that the user can choose from
     * @param title title for the selection menu
     * @param min_width minimum display width for the menu
     * @return Pointer to the selected tram line. The program terminates if the selected tram is not found.
     */
    const tramLine* reqTramSelec(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int min_width);

    /**
     * @brief Requests user to select start and end stations
     * @param title_stdec0 Title for the start station selection menu.
     * @param title_stdec1 Title for the end station selection menu.
     * @param tramline_ptr Pointer to the selected tram line
     * @param min_width Minimum display width for the station selection menu
     * @return A vector of selected station names, with the first element being the start station and the second being the end station.
     */
    vector<string> reqStationsSelect(string title_stdec0, string title_stdec1, const tramLine* tramline_ptr, int min_width);

    /**
     * @brief Calculates the price for a given route
     * @param tram_ptr Pointer to the tram line
     * @param stations Vector containing start and end station names
     * @return Calculated route price
     */
    int fetchRoutePrice(const tramLine* tram_ptr, const vector<string>& stations);

    /**
     * @brief Asks the user if they wish to continue
     * @param msg Message to display to the user
     * @return True if user wants to continue false otherwise
     */
    bool reqContinue(string msg, int min_width);

    /**
     * @brief Finalizes the ticket purchase or allows skipping
     * @param sel_route The selected route details, including tram, stations, and price.
     * @param reservoir The money reservoir for handling change.
     * @param msg_moneyout Message for displaying dispensed change.
     * @param title Title for the finalization menu.
     * @param msg_station0 Message label for the start station.
     * @param msg_station1 Message label for the end station.
     * @param msg_tram_number Message label for the tram line number.
     * @param msg_price Message label for the price.
     * @param msg_cancel Message for the cancel option.
     * @param min_width Minimum display width for the finalization menu.
     */
    void finalizeOrSkip(const route& sel_route, change& reservoir, string msg_moneyout, string title, string msg_station0, string msg_station1, string msg_tram_number, string msg_price, string msg_cancel, int min_width);
}

#endif