#include "uiUtil.h"
#include "errorHandler.h"

#if __has_include("ioUtil.h")
    #include "ioUtil.h"
    #define IOHEADEREXISTS true
#else
    #define IOHEADEREXISTS false
#endif

#include <string>
#include <vector>

using namespace std;

static int getVisualLength(const string& s) {
    int len = 0;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = s[i];

        //determine by leading bits
        if ((c & 0x80) == 0) i += 1;  //1-byte character (0xxxxxxx)
        else if ((c & 0xE0) == 0xC0) i += 2; //2-byte character (110xxxxx)
        else if ((c & 0xF0) == 0xE0) i += 3; //3-byte character (1110xxxx)
        else if ((c & 0xF8) == 0xF0) i += 4; //4-byte character (11110xxx)
        else i += 1; //treat unexpected byte as 1-byte
        
        len++;
    }
    return len;
}

static void makeStringEven(string& s) {
    if (getVisualLength(s) % 2 != 0) s += " ";
}

static int calcWidthFromVec(int min_width, vector<string> vec) {
    int width = min_width;

    for (string& line : vec) {
        makeStringEven(line);
        int lineVL = getVisualLength(line);
        if (lineVL % 2 != 0) line += " ";
        if (lineVL > width) width = lineVL;
    }

    return width;
}

namespace UiUtil {
    void dependencyCheck() {
        if (!IOHEADEREXISTS) ErrLogger::stopAndLog(300, true); //ui Util error 300: could not load ioUtil dependecy in ui-Util
    }

    vector<string> convertIntVecToStr(const vector<int>& ints) {
        vector<string> strings;
        for (int i : ints) {
            strings.push_back(to_string(i));
        }
        return strings;
    }

    string repeatUTF8string(int count, string input) {
        string result;
        while (count-- > 0) result += input;
        return result;
    }

    string drawBox(string title, vector<string> msg, int min_width) {
        makeStringEven(title);
        int width = calcWidthFromVec(min_width, msg);

        string result = "/" + repeatUTF8string((width-getVisualLength(title))/2-2, "-") + "[" + format::BOLD + title + format::RESET + "]" + repeatUTF8string((width-getVisualLength(title))/2-2, "-") + "\\\n";

        for (string& line : msg) {
            result += "|" + repeatUTF8string((width-getVisualLength(line)-2)/2, " ") + format::ITALIC + line + format::RESET + repeatUTF8string((width-getVisualLength(line)-1)/2, " ") + "|\n";
        }

        result += "\\" + repeatUTF8string(width-2, "-") + "/\n";

        return result;
    }
}