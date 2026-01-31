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
    void dependencyChecks();

    /**
     * @brief Requests user to select a tram line
     * @param all_trams vector of all available tram lines
     * @param valid_ids vector of valid tram IDs
     * @param title title for the selection menu
     * @param width display width for the menu
     * @return Pointer to the selected tram line or nullptr if cancelled
     */
    const tramLine* reqTramSelec(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int min_width);

    /**
     * @brief Requests user to select start and end stations
     * @param tramline_ptr Pointer to the selected tram line
     * @param width Display width for the station selection menu
     * @return Vector of selected station names (start and end)
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
    bool reqContinue(string msg);

    /**
     * @brief Finalizes the ticket purchase or allows skipping
     * @param sel_route The selected route details
     * @param msg_tram_number Message for tram number display
     * @param msg_price Message for price display
     * @param msg_quit Message for quit option
     */
    void finalizeOrSkip(const route& sel_route, string msg_tram_number, string msg_price, string msg_quit);
};

#endif