#pragma once
#include <vector>
#include <string>

using namespace std;

struct TramLine {
    int tram_number;
    float price_per_station;
    vector<string> stations;
};

class TramManager {
    public:
    static vector<TramLine> loadTrams(string data_dir);
    static TramLine* getTram(vector<TramLine>& loaded_trams, int tram_number);
    static int getStationDistance(TramLine* tram, string start_station, string end_station);
};
