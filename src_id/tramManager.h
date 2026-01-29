#pragma once
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Represents a single tram line with its properties.
 */
struct TramLine {
    int tram_number; /**< The unique identifier for the tram line. */
    int price_per_station; /**< The cost per station for this tram line. */
    vector<string> stations; /**< A list of station names in order for this tram line. */
};

/**
 * @brief Manages the loading, retrieval, and calculation of information related to tram lines.
 */
class TramManager {
    public:
    /**
     * @brief Loads tram line data from a specified directory.
     *        It scans for '.tram' files, parses them, and populates a vector of TramLine objects.
     * @param data_dir The path to the directory containing '.tram' data files.
     * @return A vector of `TramLine` objects successfully loaded.
    **/
    static vector<TramLine> loadTrams(string data_dir);

    /**
     * @brief Retrieves a pointer to a `TramLine` object from a vector based on its tram number.
     * @param loaded_trams A reference to the vector of `TramLine` objects to search within.
     * @param tram_number The unique number of the tram line to find.
     * @return A pointer to the `TramLine` object if found, otherwise `nullptr`.
    **/
    static TramLine* getTram(vector<TramLine>& loaded_trams, int tram_number);

    /**
     * @brief Calculates the distance (number of stations) between two specified stations
     *        on a given tram line.
     * @param tram A pointer to the `TramLine` object on which to calculate the distance.
     * @param start_station The name of the starting station.
     * @param end_station The name of the ending station.
     * @return The absolute difference in indices between the start and end stations.
     *         Returns 0 if either station is not found or they are the same.
    **/
    static int getStationDistance(TramLine* tram, string start_station, string end_station);
};
