#include "uiFormat.hpp"
#include "monCalc.hpp"

#include <iostream>
#include <vector>

using namespace std;

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

void makeStringEven(string& s) {
    if (getVisualLength(s) % 2 != 0) s += " ";
}

// keep in code from older stages because its more flexible than string(count, char)
string Ui::repeatUTF8string(int count, string input) {
    string result;
    while (count-- > 0) result += input;
    return result;
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

string Ui::drawBox(string title, vector<string> msg, int min_width) {
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

vector<string> Ui::changeToVec(change money) {
    vector<string> result;

    auto addIfVal = [&](string label, int count) {
        if (count > 0) {
            result.push_back(label + std::to_string(count));
        }
    };

    addIfVal("500€: ", money.fiveH_e);
    addIfVal("200€: ", money.twoH_e);
    addIfVal("100€: ", money.oneH_e);
    addIfVal("50€: ",  money.fifty_e);
    addIfVal("20€: ",  money.twenty_e);
    addIfVal("10€: ",  money.ten_e);
    addIfVal("5€: ",   money.five_e);
    addIfVal("2€: ",   money.two_e);
    addIfVal("1€: ",   money.one_e);
    addIfVal("50c: ",  money.fifty_c);
    addIfVal("20c: ",  money.twenty_c);
    addIfVal("10c: ",  money.ten_c);
    addIfVal("5c: ",   money.five_c);
    addIfVal("2c: ",   money.two_c);
    addIfVal("1c: ",   money.one_c);

    return result;
}