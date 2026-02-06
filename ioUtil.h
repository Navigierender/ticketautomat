#ifndef IO_UTIL_H
#define IO_UTIL_H

#include <string>
#include <vector>

using namespace std;

namespace IoUtil {
    /**
     * @brief Checks for necessary external dependencies. If a dependency is missing, it logs a critical error and terminates the program.
    **/
    void dependencyCheck();

    /**
     * @brief Clears the console
    **/
    void clearConsole();

    /**
     * @brief awaits input before continuing
    **/
    void awaitInput(string msg);

    /**
     * @brief provides a input check for beeing an element of the given vector of strings (valid)
     * @param msg input message
     * @param wrng_msg wrong input message
     * @param valid vector of valid input strings
     * @return valid checked input
    **/
    string strValInStrict(string msg, string wrng_msg, vector<string> valid);

    /**
     * @brief provides a input check for beeing an element of the given vector of integers (valid)
     * @param msg input message
     * @param wrng_msg wrong input message
     * @param valid vector of valid input integers
     * @return valid checked input
    **/
    int intValInStrict(string msg, string wrng_msg, vector<int> valid);

    /**
     * @brief Prompts for an integer input that must be greater than or equal to a goal value.
     * @param msg Input message to display
     * @param wrng_msg Error message for invalid input
     * @param goal The minimum acceptable input value
     * @return The validated integer input
     */
    int valAboveOrZero(string msg, string wrng_msg, int goal);
}

#endif