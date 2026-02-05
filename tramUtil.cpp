#include "tramUtil.h"
#include "errorHandler.h"

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;

namespace intern {
    void parseHeader(ifstream& file, tramLine& t) {
        string s;
        if (getline(file, s)) {
            while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) s.pop_back();
            size_t pos = s.find(' ');
            if (pos != string::npos) t.tram_number = stoi(s.substr(pos + 1));
        }
        if (getline(file, s)) t.station_price = stof(s);
    }

    void parseStations(ifstream& file, tramLine& t) {
        string s;
        while (getline(file, s)) {
            if (!s.empty() && s.back() == '\r') s.pop_back();
            if (!s.empty()) t.stations.push_back(s);
        }
    }

    bool tryParseTramFile(const filesystem::path& path, tramLine& t) {
        ifstream file(path);
        if (!file.is_open()) { 
            ErrLogger::Log(101, true); 
            return false; 
        }
        try {
            parseHeader(file, t);
            parseStations(file, t);
            return true;
        } catch (const invalid_argument&) {
            ErrLogger::Log(102, true);
        } catch (const out_of_range&) {
            ErrLogger::Log(102, true);
        }
        return false;
    }
}

namespace TramUtil {
    const vector<tramLine> loadTrams() {
        vector<tramLine> all_trams;
        for (const auto& entry : filesystem::directory_iterator(".")) {
            tramLine t;
            if (entry.is_regular_file() && entry.path().extension() == ".tram") {
                if (intern::tryParseTramFile(entry.path(), t)) {
                    all_trams.push_back(t);
                }
            }
        }
        if (all_trams.empty()) ErrLogger::stopAndLog(103, true);
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
        ErrLogger::stopAndLog(105, true); 
        return all_trams[0]; //for compiler warnings
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