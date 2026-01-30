#include "uiUtil.h"

#include <iostream>
#include <cstdlib> //for system calls
#include <string>
#include <vector>

using namespace std;

namespace {
    void makeStringEven(string& s) {
        if (getVisualLength(s) % 2 != 0) s += " ";
    }

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

namespace UiUtil {
    string repeatUTF8string(int count, string input) {
        string result;
        while (count-- > 0) result += input;
        return result;
    }

    string selectionBox(string title, vector<string> msg, vector<string> selec_opts, int min_width) {
        makeStringEven(title);
        int width = calcWidthFromVec(min_width, msg);
        string result = "/" + repeatUTF8string((width-getVisualLength(title))/2-2, "-") + "[" + format::BOLD + title + format::RESET + "]" + repeatUTF8string((width-getVisualLength(title))/2-2, "-") + "\\\n";

        for (string& line : msg) {
            result += "|" + repeatUTF8string((width-getVisualLength(line)-2)/2, " ") + format::ITALIC + line + format::RESET + repeatUTF8string((width-getVisualLength(line)-1)/2, " ") + "|\n";
        }

        result += "\\" + repeatUTF8string(width-2, "-") + "/\n";

        return result;
    }

    void clearConsole() {
        cout << "\033[2J\033[1;1H"; //ansii escape code to clear screen and move cursor to top left
    }
}