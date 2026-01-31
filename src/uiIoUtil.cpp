#include "uiioUtil.h"
#include "errorHandler.h"

#include <iostream>
#include <cstdlib> //for system calls
#include <string>
#include <vector>

using namespace std;

namespace {
    /**
     * @brief Ensures the visual length of a string is even by appending a space if needed
     * @param s Reference to the string to modify
     */
    void makeStringEven(string& s) {
        if (getVisualLength(s) % 2 != 0) s += " ";
    }

    /**
     * @brief Calculates the appropriate display width based on minimum width and string vector content
     * @param min_width The minimum width allowed
     * @param vec Vector of strings to consider for width calculation
     * @return Calculated width
     */
    int calcWidthFromVec(int min_width, vector<string> vec) {
        int width = min_width;

        for (string& line : vec) {
            makeStringEven(line);
            int lineVL = getVisualLength(line);
            if (lineVL % 2 != 0) line += " ";
            if (lineVL > width) width = lineVL;
        }

        return width;
    }

    /**
     * @brief Calculates the visual length of a UTF-8 string considering multi-byte characters
     * @param s The UTF-8 string
     * @return The visual length of the string
     */
    int getVisualLength(const string& s) {
        int len = 0;
        for (size_t i = 0; i < s.size(); ) {
            unsigned char c = s[i];

            if ((c & 0x80) == 0)        i += 1;
            else if ((c & 0xE0) == 0xC0) i += 2;
            else if ((c & 0xF0) == 0xE0) i += 3;
            else if ((c & 0xF8) == 0xF0) i += 4;
            else                         i += 1;

            len++;
        }
        return len;
    }
}

namespace UiIo {
    /**
     * @brief Provides input validation for a string to be an element of a given vector of valid strings
     * @param msg Input message prompt
     * @param wrng_msg Wrong input message
     * @param valid Vector of valid inputs
     * @return Valid checked input string
     */
    string valInStrict(string msg, string wrng_msg, vector<string> valid) {
        string input;

        while (true) {
            cout << msg << ": ";
            getline(cin, input);
            for (const string& v : valid) { if (input == v) return input; }
            cout << format::RED << wrng_msg << format::RESET << format::up(1) << format::clear_line;
        }
    }

    /**
     * @brief Provides input validation for an integer to be within a given range
     * @param msg Input message prompt
     * @param wrng_msg Wrong input message
     * @param range_start Start of valid input range
     * @param range_end End of valid input range
     * @return Valid checked input integer
     */
    int valInRange(string msg, string wrng_msg, int range_start, int range_end) {
        int input;

        while (true) {
            cout << msg << ": ";
            cin >> input;

            if (range_start <= input && input <= range_end) return input;

            cout << format::RED << wrng_msg << format::RESET << format::up(1) << format::clear_line;
        }
    }
}

namespace UiUtil {
    /**
     * @brief Repeats a UTF-8 string a specified number of times
     * @param count Number of times to repeat the string
     * @param input The UTF-8 string to repeat
     * @return The repeated string
     */
    string repeatUTF8string(int count, string input) {
        string result;
        while (count-- > 0) result += input;
        return result;
    }

    string drawBox(string title, vector<string> msg, int min_width) {
        // I did not include width adjustments for the title since these are programmer issues and not probable user failures
        makeStringEven(title);
        int width = calcWidthFromVec(min_width, msg);

        string result = "/" + repeatUTF8string((width-getVisualLength(title))/2-2, "-") + "[" + format::BOLD + title + format::RESET + "]" + repeatUTF8string((width-getVisualLength(title))/2-2, "-") + "\\\n";

        for (string& line : msg) {
            result += "|" + repeatUTF8string((width-getVisualLength(line)-2)/2, " ") + format::ITALIC + line + format::RESET + repeatUTF8string((width-getVisualLength(line)-1)/2, " ") + "|\n";
        }

        result += "\\" + repeatUTF8string(width-2, "-") + "/\n";

        return result;
    }

    /**
     * @brief Generates a formatted selection box for user interaction
     * @param title Title of the selection box
     * @param msg Vector of messages to display in the box
     * @param opts Vector of options for the user to select
     * @param min_w Minimum width of the selection box
     * @return Formatted string representing the selection box
     */
    string selectionBox(string title, vector<string> msg, vector<string> opts, int min_w) {
        if (opts.empty()) ErrLogger::stopAndLog(201, true);
        int idx = 0, w = calcWidthFromVec(min_w, msg);
        for (const string& o : opts) if (getVisualLength(o) + 8 > w) w = getVisualLength(o) + 8;
        while (true) {
            UiUtil::clearConsole();
            cout << "/" << repeatUTF8string((w-getVisualLength(title))/2-2, "-") << "[" << format::BOLD << title << format::RESET << "]" << repeatUTF8string((w-getVisualLength(title)-1)/2-1, "-") << "\\\n";
            for (string l : msg) cout << "|" << repeatUTF8string((w-getVisualLength(l)-2)/2, " ") << format::ITALIC << l << format::RESET << repeatUTF8string((w-getVisualLength(l)-1)/2, " ") << "|\n";
            cout << "|" << repeatUTF8string(w-2, "-") << "|\n";
            for (int i = 0; i < opts.size(); ++i) {
                string s = (i == idx ? "> [" + opts[i] + "]" : "  " + opts[i] + " ");
                cout << "|" << repeatUTF8string((w-getVisualLength(s)-2)/2, " ") << (i == idx ? string(format::BOLD) + format::GREEN : "") << s << format::RESET << repeatUTF8string((w-getVisualLength(s)-1)/2, " ") << "|\n";
            }
            cout << "\\" << repeatUTF8string(w-2, "-") << "/\nInput (W/S/Enter): ";
            string in; getline(cin, in);
            if (in.empty()) return opts[idx];
            if (tolower(in[0]) == 'w') idx = (idx - 1 + opts.size()) % opts.size();
            else if (tolower(in[0]) == 's') idx = (idx + 1) % opts.size();
        }
    }
}