#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#include <vector>
#include "tramManag.h" // Ensure tramLine and route structs are defined here

/**
 * @namespace Orst
 * @brief Orchestrates UI and Backend interaction for the Tram System
 */
namespace Orst {

    /**
     * @brief Displays a selection menu and returns a pointer to the chosen tram
     * @param all_trams The vector containing all available tramLine objects
     * @param valid_ids A vector of valid IDs for input validation
     * @param width The UI display width for boxes
     * @return const tramLine* Pointer to the selected tramLine from the collection
     */
    const tramLine* reqTramSelec(const std::vector<tramLine>& all_trams, const std::vector<int>& valid_ids, int width);

    /**
     * @brief Handles the interactive selection process for all stations on a specific tram line, does not allow selection of two elements of the same type!
     * @param tramline_ptr Pointer to the currently selected tramLine object to extract station data from
     * @param width The visual width used for rendering the UI selection boxes
     * @return std::vector<std::string> : A collection of validated station names selected by the user
     */
    const vector<string> reqStationsSelec(tramLine* tramline_ptr, int width);

    /**
     * @brief calculates and retrieves the total ticket price for the current route selection
     * @param tramline_ptr pointer to the tramLine used (contains line-specific pricing/type)
     * @param stations vector of selected station names (used to calculate distance/count)
     * @return const int : the final calculated price
     */
    const int fetchRoutePrice(sel_route.tram_ptr, sel_route.stations);

    const bool reqContinue(string msg);

    const void finalizeOrSkip(string msg);
}

#endif