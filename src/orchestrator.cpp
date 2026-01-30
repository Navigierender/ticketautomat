#include "tramUtil.h"
#include "uiUtil.h"
#include "moneyUtil.h"
#include "tramUtil.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace Orst {
    const tramLine* reqTramSelect(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int width) {
        
        cout << UiUtil::drawBox(title, valid_ids, width);
        int choice = IoUtil::valInStrict("Eingabe ID", "Ungültige ID!", valid_ids);
        return TramUtil::getTram(all_trams, choice);
    }

    vector<string> reqStationsSelect(const tramLine* tramline_ptr, int width) {};

    int fetchRoutePrice(const tramLine* tram_ptr, const vector<string>& stations) {};

    bool reqContinue(string msg) {};

    void finalizeOrSkip(const route& sel_route, string msg_tram_number, string msg_price, string msg_quit) {};
};

    /*
     * @brief Handles the interactive selection process for all stations on a specific tram line, does not allow selection of two elements of the same type!
     * @param tramline_ptr Pointer to the currently selected tramLine object to extract station data from
     * @param width The visual width used for rendering the UI selection boxes
     * @return std::vector<std::string> : A collection of validated station names selected by the user

    const vector<string> reqStationsSelec(tramLine* tramline_ptr, int width);

    /**
     * @brief calculates and retrieves the total ticket price for the current route selection
     * @param tramline_ptr pointer to the tramLine used (contains line-specific pricing/type)
     * @param stations vector of selected station names (used to calculate distance/count)
     * @return const int : the final calculated price

    const int fetchRoutePrice(sel_route.tram_ptr, sel_route.stations);

    /**
     * @brief prompts the user for a continuation decision (yes/no)
     * @param msg the message or question to be displayed to the user
     * @return const bool : true if the user chooses to continue, false otherwise

    const bool reqContinue(string msg);

    /**
     * @brief displays the final route summary or skips based on user interaction
     * @details renders the tram number, calculated price, and an exit message to the console
     * @param sel_route the completed route object containing all selection data
     * @param msg_tram_number label or message for the tram identification
     * @param msg_price label or message for the final price display
     * @param msg_quit message displayed when the process is terminated or skipped
     * @return const void

    const void finalizeOrSkip(route sel_route, string msg_tram_number, string msg_price, string msg_quit);*/