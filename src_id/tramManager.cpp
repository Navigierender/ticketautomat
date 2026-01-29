#include "tramManager.h"

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;

//returns vector of all loaded/found trams
vector<TramLine> TramManager::loadTrams(string data_dir) {
    vector<TramLine> all_trams;

    if (!filesystem::exists(data_dir)) return all_trams;
    for (const filesystem::directory_entry& entry : filesystem::directory_iterator(data_dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".tram") {
            ifstream file(entry.path());
            if (!file.is_open()) continue;
            TramLine line;
            string line_str;

            // Read tram number
            if (getline(file, line_str)) {
                // Remove trailing carriage return or space for robustness
                while (!line_str.empty() && (line_str.back() == '\r' || line_str.back() == ' ')) { line_str.pop_back(); }
                size_t space_pos = line_str.find(' ');
                if (space_pos != string::npos) { line.tram_number = stoi(line_str.substr(space_pos + 1)); }
            }

            // Read price per station
            if (getline(file, line_str)) { 
                // Remove trailing carriage return or space for robustness
                while (!line_str.empty() && (line_str.back() == '\r' || line_str.back() == ' ')) { line_str.pop_back(); }
                line.price_per_station = stof(line_str); 
            }

            // Read stations
            while (getline(file,line_str)) {
                if (!line_str.empty()) {
                    if (line_str.back() == '\r') line_str.pop_back(); // Remove carriage return
                    line.stations.push_back(line_str);
                }
            }

            all_trams.push_back(line);
        }
    }
    return all_trams;
};

//returns pointer of Tram with specified tram_number
TramLine* TramManager::getTram(vector<TramLine>& loaded_trams, int tram_number) {
    for (auto& line : loaded_trams) { if (line.tram_number == tram_number) return &line; }
    return nullptr;
};

int TramManager::getStationDistance(TramLine* tram,string start_station, string end_station) {
    int start_idx = -1;
    int end_idx = -1;

    for (int i = 0; i < tram->stations.size(); i++) {
        if (tram->stations[i] == start_station) start_idx = i;
        if (tram->stations[i] == end_station) end_idx = i;
    }

    if (start_idx != -1 && end_idx != -1) {
        return abs(start_idx - end_idx);
    }
    return 0; // Return 0 if one or both stations are not found
};
