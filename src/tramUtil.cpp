#include "tramUtil.h"
#include "errorHandler.h"

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;

namespace TramUtil {
    const vector<tramLine> loadTrams(string data_dir) {
        vector<tramLine> all_trams;

        if (!filesystem::exists(data_dir)) {
            ErrLogger::stopAndLog(100, true); //tram_data dir missing
        }

        for (const auto& entry : filesystem::directory_iterator(data_dir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".tram") {
                ifstream file(entry.path());
                
                if (!file.is_open()) {
                    ErrLogger::Log(101, true); //could not open specific tram file
                    continue;
                }

                tramLine line;
                string line_str;

                try {
                    if (getline(file, line_str)) {
                        // Remove trailing carriage returns or spaces from the line string
                        while (!line_str.empty() && (line_str.back() == '\r' || line_str.back() == ' ')) {
                            line_str.pop_back();
                        }
                        size_t space_pos = line_str.find(' ');
                        if (space_pos != string::npos) {
                            line.tram_number = stoi(line_str.substr(space_pos + 1));
                        }
                    }
                    
                    if (getline(file, line_str)) line.station_price = stof(line_str);

                    while (getline(file, line_str)) {
                        if (!line_str.empty()) {
                            if (line_str.back() == '\r') line_str.pop_back();
                            line.stations.push_back(line_str);
                        }
                    }
                    
                    all_trams.push_back(line);
                    
                } catch (const invalid_argument&) {
                        ErrLogger::Log(102, true); //tried to read corrupted tram file (invalid format)
                    continue;
                } catch (const out_of_range&) {
                    ErrLogger::Log(102, true); //tried to read corrupted tram file (invalid format)
                    continue;
                }
            }
        }
                    
        if (all_trams.empty()) {
            ErrLogger::stopAndLog(103, true); //no valid tram lines could be loaded
        }
                    
        return all_trams;
    }
                    
    const vector<int> getTramINTs(const vector<tramLine>* tram_lines) {
        vector<int> tram_ints;
        for (const auto& tram : *tram_lines) {
            tram_ints.push_back(tram.tram_number);
        }
        return tram_ints;
    }

    const tramLine& getTram(const vector<tramLine>& all_trams, int choice) {
        for (const auto& tram : all_trams) {
            if (tram.tram_number == choice) {
                return tram;
            }
        }
        ErrLogger::stopAndLog(105, true); // Requested tram line not found
    }
                    
    int getStationDistance(const tramLine* tram, vector<string> prov_stations) {
        int start_idx = -1;
        int end_idx = -1;

        for (int i = 0; i < (int)tram->stations.size(); i++) {
            if (tram->stations[i] == prov_stations[0]) start_idx = i;
            if (tram->stations[i] == prov_stations[1]) end_idx = i;
        }

        if (start_idx == -1 || end_idx == -1) ErrLogger::stopAndLog(104,true);

        return abs(start_idx - end_idx);
    }
}