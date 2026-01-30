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
    const vector<tramLine> loadTrams(string data_dir);
};

#endif