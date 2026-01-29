#include "io.h"
#include "uiFormat.h"
#include <iostream>

using namespace std;

string Io::valInStrict(string msg, string wrng_msg, vector<string> valid) {
    string input;

    while (true) {
        cout << msg << ": ";
        getline(cin, input);
        for (const string& v : valid) { if (input == v) return input; }
        cout << format.RED << wrng_msg << format.RESET << format::up(1) << format.clear_line;
    }
}

int Io::valInRange(string msg, string wrng_msg, int range_start, int range_end) {
    int input;

    while (true) {
        cout << msg << ": ";
        cin >> input;

        if (range_start <= input && input <= range_end) return input;

        cout << format.RED << wrng_msg << format.RESET << format::up(1) << format.clear_line;
    }
}

float Io::valAbove(string msg, string wrng_msg, float goal) {
    float input;

    while (true) {
        cout << msg << ": ";
        cin >> input;

        if (input >= goal) return input;

        cout << format.RED << wrng_msg << format.RESET << format::up(1) << format.clear_line;
    }
}