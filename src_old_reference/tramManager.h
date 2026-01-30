#pragma once
#include <vector>
#include <string>

using namespace std;

struct TramLine {
    int tram_number;
    int price_per_station;
    vector<string> stations;
};

class TramManager {
    public:

    /**
     * @brief loads all tram line configurations from a specified directory
     * @param data_dir path to the directory containing .tram files
     * @return vector of all successfully loaded TramLine objects
    **/
    static vector<TramLine> loadTrams(string data_dir);

    /**
     * @brief finds a specific tram line by its number within a vector
     * @param loaded_trams reference to the vector of available tram lines
     * @param tram_number the identification number of the tram to find
     * @return pointer to the found TramLine or nullptr if not found
    **/
    static TramLine* getTram(vector<TramLine>& loaded_trams, int tram_number);

    /**
     * @brief calculates the number of stops between two stations on a tram line
     * @param tram pointer to the tram line to check
     * @param start_station name of the departure station
     * @param end_station name of the destination station
     * @return absolute distance in number of stations
    **/
    static int getStationDistance(TramLine* tram, string start_station, string end_station);
};
