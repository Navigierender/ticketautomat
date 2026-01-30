#include "tramUtil.h"
#include "errorHandler.h"

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;

const vector<tramLine> TramUtil::loadTrams(string data_dir) {
    vector<tramLine> all_trams;

    if (!filesystem::exists(data_dir)) {
        ErrLogger::stopAndLog(101, true); //tram_data dir missing
    }

    for (const auto& entry : filesystem::directory_iterator(data_dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".tram") {
            ifstream file(entry.path());
            
            if (!file.is_open()) {
                ErrLogger::Log(102, true); //could not open specific tram file
                continue;
            }

            tramLine line;
            string line_str;

            try {
                if (getline(file, line_str)) {
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
                    ErrLogger::Log(103, true); //tried to read corrupted tram file (invalid format)
                continue;
            } catch (const out_of_range&) {
                ErrLogger::Log(103, true); //tried to read corrupted tram file (invalid format)
                continue;
            }
        }
    }

    if (all_trams.empty()) {
        ErrLogger::stopAndLog(104, true); //no valid tram lines could be loaded
    }

    return all_trams;
}