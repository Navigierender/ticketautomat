#pragma once
#include "monCalc.h"

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

    static string up(int n) { return "\033[" + to_string(n) + "A"; }
    static string down(int n) { return "\033[" + to_string(n) + "B"; }
};

inline format format;

class Ui {
public:

    /**
     * @brief creates a string by repeating a UTF-8 input multiple times
     * @param count how many times to repeat
     * @param input the string or character to repeat
     * @return the concatenated result string
    **/
    static string repeatUTF8string(int count, string input);

    /**
     * @brief draws an ASCII box with a centered title and message lines
     * @param title text displayed in the top border
     * @param msg vector of strings to be displayed inside the box
     * @param min_width minimum width of the box
     * @return formatted string containing the full ASCII box
    **/
    static string drawBox(string title, vector<string> msg, int min_width);

    /**
     * @brief converts a change struct into a printable vector of strings
     * @param money the change struct to be converted
     * @return vector containing labels and counts for coins > 0
    **/
    static vector<string> changeToVec(change money);
};