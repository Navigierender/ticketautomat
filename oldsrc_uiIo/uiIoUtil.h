#ifndef UIIO_UTIL_H
#define UIIO_UTIL_H

#include <vector>
#include <string>

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

namespace IoUtil {
    /**
     * @brief provides a input check for beeing an element of the given vector of strings (valid)
     * @param msg input message
     * @param wrng_msg wrong input message
     * @param valid vector of valid inputs/
     * @return string : valid checked input
    **/
    static string valInStrict(string msg, string wrng_msg, vector<string> valid);

    /**
     * @brief provides a input check for beeing inside of the given range
     * @param msg input message
     * @param wrng_msg Wrong input Message
     * @param range_start start of valid input range
     * @param range_end end of valid input range
     * @return int : valid checked input
    **/
    static int valInRange(string msg, string wrng_msg, int range_start, int range_end);
}

namespace UiUtil {
    /**
     * @brief Generates a formatted selection box for user interaction
     * @param title Title of the selection box
     * @param msg Vector of messages to display in the box
     * @param opts Vector of options for the user to select
     * @param minwidth Minimum width of the selection box
     * @return Formatted string representing the selection box
     */
    string selectionBox(string title, vector<string> msg, vector<string> opts, int minwidth);
    /**
     * @brief Repeats a UTF-8 string a specified number of times
     * @param count Number of times to repeat the string
     * @param input The UTF-8 string to repeat
     * @return The repeated string
     */
    string repeatUTF8string(int count, string input);

    static string drawBox(string title, vector<string> msg, int min_width);

    /**
     * @brief Clears the console screen
     */
    void clearConsole();
}

#endif