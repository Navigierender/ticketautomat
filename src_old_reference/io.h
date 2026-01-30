#pragma once

#include <string>
#include <vector>

class Io {
public:

    /**
     * @brief provides a input check for beeing an element of the given vector of strings (valid)
     * @param msg input message
     * @param wrng_msg wrong input message
     * @param valid vector of valid inputs/
     * @return string : valid checked input
    **/
    static std::string valInStrict(std::string msg, std::string wrng_msg, std::vector<std::string> valid);

    /**
     * @brief provides a input check for beeing inside of the given range
     * @param msg input message
     * @param wrng_msg Wrong input Message
     * @param range_start start of valid input range
     * @param range_end end of valid input range
     * @return int : valid checked input
    **/
    static int valInRange(std::string msg, std::string wrng_msg, int range_start, int range_end);

    static int valUnder_oZERO(std::string msg, std::string wrng_msg, int goal);
};
