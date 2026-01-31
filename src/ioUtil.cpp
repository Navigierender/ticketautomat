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
        if (!UIHEADEREXISTS) ErrLogger::stopAndLog(400, false); //io Util error 400: could not load uiUtil dependecy in io-Util
    }

    void clearConsole() {
        cout << "\033[2J\033[H";
    }

    string valInStrict(string msg, string wrng_msg, vector<string> valid) {
        string input;

        while (true) {
            cout << msg << ": ";
            getline(cin, input);
            for (const string& v : valid) { if (input == v) return input; }
            cout << format::RED << wrng_msg << format::RESET << format::up(1) << format::clear_line;
        }
    }
}