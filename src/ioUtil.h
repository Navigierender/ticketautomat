#ifndef IO_UTIL_H
#define IO_UTIL_H

#include <string>
#include <vector>

using namespace std;

namespace IoUtil {
    void dependencyCheck();

    void clearConsole();

    /**
     * @brief provides a input check for beeing an element of the given vector of strings (valid)
     * @param msg input message
     * @param wrng_msg wrong input message
     * @param valid vector of valid inputs/
     * @return valid checked input
    **/
    string strValInStrict(string msg, string wrng_msg, vector<string> valid);

    /**
     * @brief provides a input check for beeing an element of the given vector of integers (valid)
     * @param msg input message
     * @param wrng_msg wrong input message
     * @param valid vector of valid inputs/
     * @return valid checked input
    **/
    int intValInStrict(string msg, string wrng_msg, vector<int> valid);

    int valAboveOrZero(string msg, string wrng_msg, int goal);
}

#endif