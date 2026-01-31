# Project Modules Documentation

This document provides an overview of the modules found in the `src` directory of this project.

## Module: `errorHandler`
**Files:** `errorHandler.h`, `errorHandler.cpp`
**Purpose:** Handles error logging and program termination. It provides functions to initialize an error list from an external file, log errors without immediate termination, and log critical errors that lead to program shutdown.
**Key Functions:**
*   `stopAndShowErrors(int id)`: Prints logged errors and terminates the program with a given exit code.
*   `initErrList(string errorlist_dir)`: Loads error descriptions from a specified colon-separated file.
*   `Log(int id, bool is_external)`: Adds an error to an internal history without stopping execution.
*   `stopAndLog(int id, bool is_external)`: Logs a critical error and immediately shuts down the program.

## Module: `ioUtil`
**Files:** `ioUtil.h`, `ioUtil.cpp`
**Purpose:** Provides utility functions for input/output operations, console management, and dependency checks. It includes functionalities for clearing the console and validating user input against a set of allowed values or a minimum threshold.
**Key Functions:**
*   `dependencyCheck()`: Verifies external dependencies and terminates if any are missing.
*   `clearConsole()`: Clears the terminal screen.
*   `strValInStrict(string msg, string wrng_msg, vector<string> valid)`: Validates string input against a vector of valid strings.
*   `intValInStrict(string msg, string wrng_msg, vector<int> valid)`: Validates integer input against a vector of valid integers.
*   `valAboveOrZero(string msg, string wrng_msg, int goal)`: Prompts for an integer input that must be greater than or equal to a specified goal.

## Module: `moneyUtil`
**Files:** `moneyUtil.h`, `moneyUtil.cpp`
**Purpose:** Manages currency denominations and change calculations. It defines a `change` struct to represent a reservoir of money in various units and provides functions to check if change can be given and to process change output.
**Key Functions:**
*   `changeOutPossible(int amount, change& reservoir)`: Checks if a given amount of change can be provided from the current reservoir.
*   `processChangeOut(int amount, change& reservoir)`: Dispenses change for a given amount, updating the reservoir and returning the dispensed denominations.
*   `changeToVector(const change& c)`: Converts a `change` struct into a vector of integer counts for each denomination.

## Module: `orchestrator`
**Files:** `orchestrator.h`, `orchestrator.cpp`
**Purpose:** Orchestrates the main program flow, handling user interactions for selecting tram lines and stations, calculating prices, and finalizing ticket purchases. It acts as a central control module, integrating functionalities from `tramUtil`, `uiUtil`, and `moneyUtil`.
**Key Functions:**
*   `dependencyChecks()`: Performs initial dependency checks specific to the orchestrator.
*   `reqTramSelec(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int min_width)`: Prompts the user to select a tram line.
*   `reqStationsSelect(string title_stdec0, string title_stdec1, const tramLine* tramline_ptr, int min_width)`: Guides the user through selecting start and end stations for a route.
*   `fetchRoutePrice(const tramLine* tram_ptr, const vector<string>& stations)`: Calculates the fare for a selected route.
*   `reqContinue(string msg, int min_width)`: Asks the user if they wish to continue an operation.
*   `finalizeOrSkip(const route& sel_route, change& reservoir, ..., int min_width)`: Manages the final steps of a ticket purchase, including displaying details and handling change.

## Module: `tramUtil`
**Files:** `tramUtil.h`, `tramUtil.cpp`
**Purpose:** Manages tram line data, including loading tram configurations from files, retrieving tram line information, and calculating distances between stations. It defines `tramLine` and `route` structs to represent tram data and selected routes.
**Key Functions:**
*   `loadTrams(string data_dir)`: Scans a directory for `.tram` files, parses them, and returns a vector of `tramLine` objects.
*   `getTramINTs(const vector<tramLine>* tram_lines)`: Extracts tram numbers from a vector of `tramLine` objects.
*   `getTram(const std::vector<tramLine>& all_trams, int choice)`: Retrieves a specific `tramLine` object by its number.
*   `getStationDistance(const tramLine* tram, vector<string> prov_stations)`: Calculates the number of stations between two specified stations on a given tram line.

## Module: `uiUtil`
**Files:** `uiUtil.h`, `uiUtil.cpp`
**Purpose:** Provides utility functions for user interface elements, including ANSI escape codes for text formatting and console cursor manipulation, and functions for drawing ASCII boxes.
**Key Functions:**
*   `dependencyCheck()`: Verifies external UI-related dependencies.
*   `convertIntVecToStr(const vector<int>& ints)`: Converts a vector of integers to a vector of strings.
*   `repeatUTF8string(int count, string input)`: Repeats a UTF-8 string a specified number of times.
*   `drawBox(string title, vector<string> msg, int min_width)`: Creates an ASCII box with a centered title and message lines.
*   `format` struct: Contains `static constexpr const char*` members for various ANSI text formatting and cursor control codes (e.g., `RESET`, `BOLD`, `RED`, `up(int n)`).
