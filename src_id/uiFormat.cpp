#include "uiFormat.h"
#include "monCalc.h"

#include <iostream>
#include <vector>

using namespace std;

// Helper function to calculate the visual length of a UTF-8 string
// This is necessary because some UTF-8 characters take more than one byte but represent a single visual character.
int getVisualLength(const string& s) {
    int len = 0;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = s[i];

        if ((c & 0x80) == 0)        i += 1; // 1-byte character (ASCII)
        else if ((c & 0xE0) == 0xC0) i += 2; // 2-byte character
        else if ((c & 0xF0) == 0xE0) i += 3; // 3-byte character
        else if ((c & 0xF8) == 0xF0) i += 4; // 4-byte character
        else                         i += 1; // Fallback for malformed or unknown (treat as 1 byte)

        len++;
    }
    return len;
}

// Helper function to make string's visual length even by appending a space if needed
void makeStringEven(string& s) {
    if (getVisualLength(s) % 2 != 0) s += " ";
}

// Implements repeatUTF8string as declared in uiFormat.h
// Kept from older stages because it's more flexible than string(count, char) for UTF-8.
string Ui::repeatUTF8string(int count, string input) {
    string result;
    while (count-- > 0) result += input;
    return result;
}

// Helper function to calculate the optimal box width based on content
int calcWidthFromVec(int min_width, vector<string> vec) {
    int width = min_width;

    for (string& line : vec) {
        // Ensure even length for centering, potentially adding a space
        makeStringEven(line);
        int lineVL = getVisualLength(line);
        if (lineVL % 2 != 0) line += " "; // Double check after makeStringEven, though it should be even already

        if (lineVL > width) width = lineVL;
    }

    // Ensure width itself is even for aesthetic centering of borders/fillers
    if (width % 2 != 0) width++; // Increase width by 1 if odd to make it even

    return width;
}

// Implements drawBox as declared in uiFormat.h
string Ui::drawBox(string title, vector<string> msg, int min_width) {
    // Title width adjustments are considered programmer issues, not user failures.
    makeStringEven(title);
    int width = calcWidthFromVec(min_width, msg);

    std::string result;

    // Top border: /----[TITLE]---- |
    result = "/" + repeatUTF8string((width - getVisualLength(title) - 2) / 2, "-") + 
             std::string("[") + format::BOLD + title + format::RESET + std::string("]") + 
             repeatUTF8string((width - getVisualLength(title) - 2) / 2, "-") + "\\\n";

    // Message lines: |    Message    |
    for (string& line : msg) {
        // Ensure even length for centering, potentially adding a space
        makeStringEven(line);
        result += "|" + repeatUTF8string((width - getVisualLength(line) - 2) / 2, " ") + 
                  format::ITALIC + line + format::RESET + 
                  repeatUTF8string((width - getVisualLength(line) - 2) / 2, " ") + "|\n";
    }

    // Bottom border: \\---------------/
    result += "\\\\" + repeatUTF8string(width - 2, "-") + "/\n";

    return result;
}

// Implements changeToVec as declared in uiFormat.h
vector<string> Ui::changeToVec(change money) {
    vector<string> result;

    // Lambda to add a denomination string if its count is greater than 0
    auto addIfVal = [&](string label, int count) {
        if (count > 0) {
            result.push_back(label + std::to_string(count));
        }
    };

    // Add denominations in descending order as per the struct's implicit value
    addIfVal("17: ",  money.seventeen);
    addIfVal("11: ",  money.eleven);
    addIfVal("7: ",   money.seven);
    addIfVal("5: ",   money.five);
    addIfVal("3: ",   money.three);
    addIfVal("2: ",   money.two);
    addIfVal("1: ",   money.one);

    return result;
}
