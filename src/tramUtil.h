#ifndef TRAM_UTIL_H
#define TRAM_UTIL_H

#include <vector>
#include <string>

using namespace std;

struct tramLine {
    int tram_number;
    int station_price;
    vector<string> stations;
};

struct route {
    const tramLine* tram_ptr;
    vector<string> stations;
    int price;
};

namespace TramUtil {
    /**
     * @brief Scans a directory for .tram files and parses them into a vector.
     * @param data_dir Path to the directory containing tram data files.
     * @return A vector of successfully parsed tramLine objects.
     * @details Stops and logs (ID 101) if directory is missing or (ID 104) if no valid trams are found.
     * Logs warnings (ID 102/103) for individual file access or format errors.
     */
    const vector<tramLine> loadTrams(string data_dir);

    const vector<int> getTramINTs(const vector<tramLine>* tram_lines);
};

#endif