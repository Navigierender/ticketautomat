#ifndef TRAM_UTIL_H
#define TRAM_UTIL_H

#include <vector>
#include <string>

using namespace std;

/**
 * @brief Represents a single tram line with its number, price per station, and list of stations.
 */
struct tramLine {
    /// @brief The unique identification number of the tram line.
    int tram_number;
    /// @brief The price charged per station traveled on this tram line.
    int station_price;
    /// @brief A vector of strings representing the names of the stations on this tram line, in order.
    vector<string> stations;
};

/**
 * @brief Represents a selected route, including the tram line, selected stations, and calculated price.
 */
struct route {
    /// @brief A pointer to the selected tram line.
    const tramLine* tram_ptr;
    /// @brief A vector of strings containing the start and end station names for the route.
    vector<string> stations;
    /// @brief The calculated price for the selected route.
    int price;
};

namespace TramUtil {
    /**
     * @brief Scans a directory for .tram files and parses them into a vector.
     * @param data_dir Path to the directory containing tram data files.
     * @return A vector of successfully parsed tramLine objects.
     * @details Stops and logs (ID 100) if the data directory is missing or (ID 103) if no valid trams are loaded.
     * Logs warnings (ID 101) for individual file access errors or (ID 102) for format errors within tram files.
     */
    const vector<tramLine> loadTrams();

    /**
     * @brief Extracts tram numbers (IDs) from a vector of tram lines
     * @param tram_lines Pointer to a vector of tramLine objects
     * @return A vector of integer tram IDs
     */
    const vector<int> getTramINTs(const vector<tramLine>* tram_lines);

    /**
     * @brief Retrieves a specific tram line by its number from a vector of tram lines.
     * @param all_trams A constant reference to a vector of all available tram lines.
     * @param choice The tram number to search for.
     * @return A constant reference to the found tramLine object.
     * @details Stops and logs (ID 105) if the requested tram line is not found.
     */
    const tramLine& getTram(const std::vector<tramLine>& all_trams, int choice);

    /**
     * @brief Calculates the distance between two provided stations on a given tram line.
     * @param tram A pointer to the tramLine object for which to calculate the distance.
     * @param prov_stations A vector of strings containing the start and end station names.
     * @return The number of stations between the start and end stations.
     * @details Logs an error (ID 104) and terminates if one of the provided stations is not found on the tram line.
     */
    int getStationDistance(const tramLine* tram, vector<string> prov_stations);
};

#endif