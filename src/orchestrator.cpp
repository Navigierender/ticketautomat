#include "orchestrator.h"
#include "UiUtils.h" // For UI::drawBox, UI::resetUIaClean, etc.
#include "ioUtils.h" // For Io::valInStrict
#include "tramManag.h"

namespace Orst {

    /**
     * @brief Requests a tram selection from the user and returns the corresponding object pointer
     * @param all_trams Vector of all available tramLine objects.
     * @param valid_ids Vector of valid integer IDs used for input validation.
     * @param width The visual width of the UI box.
     * @return const tramLine* Pointer to the selected tramLine object.
     */
    const tramLine* requestTramSelection(const std::vector<tramLine>& all_trams, const std::vector<int>& valid_ids, int width) {
        
        std::cout << UI::drawBox("Bahnauswahl", valid_ids, width);
        int choice = Io::valInStrict("Eingabe ID", "Ungültige ID!", valid_ids);
        return TramManag::getTram(all_trams, choice);
    }
}