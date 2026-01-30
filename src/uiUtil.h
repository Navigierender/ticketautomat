#ifndef UI_UTIL_H
#define UI_UTIL_H

using namespace std;

namespace UiUtil {
    struct format {
        static constexpr const char* RESET = "\033[0m";

        static constexpr const char* BOLD = "\033[1m";
        static constexpr const char* ITALIC = "\033[3m";
        static constexpr const char* UNDERLINE = "\033[4m";

        static constexpr const char* RED = "\033[31m";
        static constexpr const char* GREEN = "\033[32m";
        static constexpr const char* WHITE = "\033[37m";

        static constexpr const char* clear_line = "\r\033[2K";

        static string up(int n) { return "\033[" + to_string(n) + "A"; }
        static string down(int n) { return "\033[" + to_string(n) + "B"; }
    };

    string selectionBox(string title, vector<string> msg, vector<string> selec_opts, int minwidth);
    string repeatUTF8string(int count, string input);
    void clearConsole();
}

#endif