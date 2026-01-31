#ifndef UI_UTIL_H
#define UI_UTIL_H

#include <string>
#include <vector>

using namespace std;

struct format {
    static constexpr const char* RESET = "\033[0m";

    static constexpr const char* BOLD = "\033[1m";
    static constexpr const char* ITALIC = "\033[3m";
    static constexpr const char* UNDERLINE = "\033[4m";

    static constexpr const char* RED = "\033[31m";
    static constexpr const char* GREEN = "\033[32m";
    static constexpr const char* WHITE = "\033[37m";

    static constexpr const char* clear_line = "\r\033[2K";

    /**
     * @brief Moves cursor up by n lines
     * @param n Number of lines to move up
     * @return ANSI escape code for moving cursor up
     */
    static string up(int n) { return "\033[" + to_string(n) + "A"; }

    /**
     * @brief Moves cursor down by n lines
     * @param n Number of lines to move down
     * @return ANSI escape code for moving cursor down
     */
    static string down(int n) { return "\033[" + to_string(n) + "B"; }
};

namespace UiUtil {
    void dependencyCheck();

    vector<string> convertIntVecToStr(const vector<int>& ints);

    /**
     * @brief creates a string by repeating a UTF-8 input multiple times
     * @param count how many times to repeat
     * @param input the string or character to repeat
     * @return the concatenated result string
    **/
    string repeatUTF8string(int count, string input);

    /**
     * @brief draws an ASCII box with a centered title and message lines
     * @param title text displayed in the top border
     * @param msg vector of strings to be displayed inside the box
     * @param min_width minimum width of the box
     * @return formatted string containing the full ASCII box
    **/
    string drawBox(string title, vector<string> msg, int min_width);
}

#endif