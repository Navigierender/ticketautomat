#pragma once

#include <string>
#include <vector>

class Io {
public:
    static std::string valInStrict(std::string msg, std::string wrng_msg, std::vector<std::string> valid);
    static int valInRange(std::string msg, std::string wrng_msg, int range_start, int range_end);
    static int valUnder_oZERO(std::string msg, std::string wrng_msg, int goal);
    static bool askToQuit();
};
