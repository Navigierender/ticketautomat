#pragma once
#include "monCalc.h" // For the change struct in changeToVec

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Contains static constexpr char* for ANSI escape codes for text formatting
 *        (e.g., colors, bold, italic, underline) and cursor manipulation.
 */
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
     * @brief Generates an ANSI escape code to move the cursor up by `n` lines.
     * @param n The number of lines to move the cursor up.
     * @return A string containing the ANSI escape code.
     */
    static string up(int n) { return "\033[" + to_string(n) + "A"; }
    /**
     * @brief Generates an ANSI escape code to move the cursor down by `n` lines.
     * @param n The number of lines to move the cursor down.
     * @return A string containing the ANSI escape code.
     */
    static string down(int n) { return "\033[" + to_string(n) + "B"; }
};

/**
 * @brief Global instance of the format struct for easy access to ANSI codes.
 *        Marked as inline to avoid multiple definition errors across translation units.
 */
inline format format;

/**
 * @brief Provides utility functions for formatting and drawing console-based user interfaces.
 */
class Ui {
public:

    /**
     * @brief Creates a string by repeating a given UTF-8 input multiple times.
     *        This function is designed to be more flexible than `std::string(count, char)`.
     * @param count The number of times the input string should be repeated.
     * @param input The string or character sequence to repeat.
     * @return The concatenated result string.
    **/
    static string repeatUTF8string(int count, string input);

    /**
     * @brief Draws an ASCII box with a centered title and multiple message lines.
     *        It automatically adjusts the width based on the content and a minimum width.
     * @param title The text to be displayed in the top border of the box.
     * @param msg A vector of strings, each representing a line to be displayed inside the box.
     * @param min_width The minimum desired width of the box. The box may be wider if content requires.
     * @return A formatted string containing the complete ASCII box.
    **/
    static string drawBox(string title, vector<string> msg, int min_width);

    /**
     * @brief Converts a `change` struct into a printable vector of strings,
     *        displaying only the denominations with a count greater than zero.
     * @param money The `change` struct containing the counts of various coin denominations.
     * @return A vector of strings, where each string represents a coin denomination
     *         and its count (e.g., "17: 2" for two 17-unit coins).
    **/
    static vector<string> changeToVec(change money);
};
