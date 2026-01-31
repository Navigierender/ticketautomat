#include "ioUtil.h"
#include "errorHandler.h"

#if __has_include("uiUtil.h")
    #include "uiUtil.h"
    #define UIHEADEREXISTS true
#else
    #define UIHEADEREXISTS false
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace IoUtil {
    void dependencyCheck() {
        if (!UIHEADEREXISTS) ErrLogger::stopAndLog(400, true); //io Util error 400: could not load uiUtil dependecy in io-Util
    }

    void clearConsole() {
        cout << "\033[2J\033[H";
    }

    string strValInStrict(string msg, string wrng_msg, vector<string> valid) {
        string input;

        while (true) {
            cout << msg << ": ";
            getline(cin, input);
            for (const string& v : valid) { if (input == v) return input; }
            cout << format::RED << wrng_msg << format::RESET << format::up(1) << format::clear_line;
        }
    }

    int intValInStrict(string msg, string wrng_msg, vector<int> valid) {
        string input;

        while (true) {
            cout << msg << ": ";
            getline(cin, input);
            //check: Is the string empty or non-numeric?
            bool numeric = !input.empty();
            for (char c : input) if (!isdigit(c)) numeric = false;

            if (numeric) {
                int val = stoi(input);
                for (int v : valid) if (val == v) return val;
            }

            cout << format::RED << wrng_msg << format::RESET << format::up(1) << format::clear_line;
        }
    }

    int valAboveOrZero(string msg, string wrng_msg, int goal) {
        string input;
        while (true) {
            cout << msg << ": ";
            getline(cin, input);

            bool numeric = !input.empty();
            for (char c : input) if (!isdigit(c)) numeric = false;

            if (numeric) {
                int val = stoi(input);
                if (val == 0 || val >= goal) return val;
            }

            cout << format::RED << wrng_msg << format::RESET << format::up(1) << format::clear_line;
        }
    }
}