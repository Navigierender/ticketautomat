#pragma once

#include <string>
#include <vector>

/**
 * @brief Provides utilities for robust user input handling and validation.
 */
class Io {
public:

    /**
     * @brief Prompts the user for input and validates it against a predefined list of valid strings.
     *        Continues to prompt with an error message until a valid input is received.
     * @param msg The message displayed to the user for input.
     * @param wrng_msg The error message displayed when invalid input is provided.
     * @param valid A vector of strings representing all acceptable inputs.
     * @return The validated user input string.
    **/
    static std::string valInStrict(std::string msg, std::string wrng_msg, std::vector<std::string> valid);

    /**
     * @brief Prompts the user for integer input and validates it to be within a specified range.
     *        Continues to prompt with an error message until a valid input is received.
     * @param msg The message displayed to the user for input.
     * @param wrng_msg The error message displayed when input is out of range.
     * @param range_start The inclusive lower bound of the valid input range.
     * @param range_end The inclusive upper bound of the valid input range.
     * @return The validated user input integer.
    **/
    static int valInRange(std::string msg, std::string wrng_msg, int range_start, int range_end);

    /**
     * @brief Prompts the user for integer input and validates it to be greater than or equal to a goal value, or zero.
     *        This function is specifically designed for scenarios where the user can input 0 to cancel/exit,
     *        or a value greater than or equal to a target.
     *        Continues to prompt with an error message until a valid input is received.
     * @param msg The message displayed to the user for input.
     * @param wrng_msg The error message displayed when input is too low (and not zero).
     * @param goal The minimum acceptable value (if not zero).
     * @return The validated user input integer.
    **/
    static int valUnder_oZERO(std::string msg, std::string wrng_msg, int goal);
};
