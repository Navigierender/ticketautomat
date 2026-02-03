#ifndef UI_UTIL_H
#define UI_UTIL_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Provides ANSI escape codes for text formatting and cursor manipulation.
 */
struct format {
    /// @brief Resets all ANSI formatting.
    static constexpr const char* RESET = "\033[0m";

    /// @brief Applies bold text formatting.
    static constexpr const char* BOLD = "\033[1m";
    /// @brief Applies italic text formatting.
    static constexpr const char* ITALIC = "\033[3m";
    /// @brief Applies underline text formatting.
    static constexpr const char* UNDERLINE = "\033[4m";

    /// @brief Sets text color to red.
    static constexpr const char* RED = "\033[31m";
    /// @brief Sets text color to green.
    static constexpr const char* GREEN = "\033[32m";
    /// @brief Sets text color to white.
    static constexpr const char* WHITE = "\033[37m";

    /// @brief Clears the current line.
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
    /**
     * @brief Checks for necessary external dependencies.
     *        If a dependency is missing, it logs a critical error and terminates the program.
     */
    void dependencyCheck();

    /**
     * @brief Converts a vector of integers to a vector of strings.
     * @param ints The input vector of integers.
     * @return A new vector containing the string representations of the integers.
     */
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