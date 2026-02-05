# Project Documentation

This document provides a summary of the submodules and their functions within this project.

## errorHandler
Handles error logging and program termination.

### Functions
- `ErrLogger::stopAndShowErrors(int id)`: Prints all logged errors and terminates the program.
- `ErrLogger::initErrList()`: Loads the error list from a colon-separated file.
- `ErrLogger::Log(int id, bool is_external)`: Adds an error to the internal history without stopping.
- `ErrLogger::stopAndLog(int id, bool is_external)`: Logs a final error and triggers immediate shutdown.

## ioUtil
Provides input/output utility functions.

### Functions
- `IoUtil::dependencyCheck()`: Checks for necessary external dependencies and terminates on failure.
- `IoUtil::clearConsole()`: Clears the console screen.
- `IoUtil::awaitInput(string msg)`: Pauses execution and waits for user input.
- `IoUtil::strValInStrict(string msg, string wrng_msg, vector<string> valid)`: Validates string input against a list of valid options.
- `IoUtil::intValInStrict(string msg, string wrng_msg, vector<int> valid)`: Validates integer input against a list of valid options.
- `IoUtil::valAboveOrZero(string msg, string wrng_msg, int goal)`: Validates that an integer input is greater than or equal to a specified value.

## moneyUtil
Manages currency and change calculations.

### Functions
- `MoneyUtil::changeOutPossible(int amount, change& reservoir)`: Checks if change can be made for a given amount.
- `MoneyUtil::processChangeOut(int amount, change& reservoir)`: Processes a change transaction, updating the money reservoir.
- `MoneyUtil::changeToVector(const change& c)`: Converts a `change` struct to a vector of integers.

## orchestrator
Coordinates the main application logic and user flow.

### Functions
- `Orst::dependencyChecks()`: Performs initial dependency checks for the orchestrator.
- `Orst::reqTramSelec(...)`: Prompts the user to select a tram line.
- `Orst::reqStationsSelect(...)`: Prompts the user to select start and end stations.
- `Orst::fetchRoutePrice(...)`: Calculates the price for a selected route.
- `Orst::reqContinue(...)`: Asks the user if they want to perform another transaction.
- `Orst::finalizeOrSkip(...)`: Handles the final ticket purchase and payment confirmation.

## tramUtil
Handles loading and managing tram line data.

### Functions
- `TramUtil::loadTrams()`: Loads tram data from `.tram` files in a specified directory.
- `TramUtil::getTramINTs(const vector<tramLine>* tram_lines)`: Extracts the tram line numbers (IDs) from a vector of tram lines.
- `TramUtil::getTram(const vector<tramLine>& all_trams, int choice)`: Retrieves a specific tram line by its number.
- `TramUtil::getStationDistance(const tramLine* tram, vector<string> prov_stations)`: Calculates the distance in stations between two points on a tram line.

## uiUtil
Provides utilities for creating text-based user interfaces.

### Functions
- `UiUtil::dependencyCheck()`: Checks for necessary external dependencies and terminates on failure.
- `UiUtil::convertIntVecToStr(const vector<int>& ints)`: Converts a vector of integers to a vector of strings.
- `UiUtil::repeatUTF8string(int count, string input)`: Repeats a string multiple times.
- `UiUtil::drawBox(string title, vector<string> msg, int min_width)`: Draws a formatted box with a title and message content.

## tester
Contains unit tests for the project.

### Functions
- `main()`: Executes all defined test cases, including `testGetStationDistance` and `testFetchRoutePrice`, and reports the results.

## main
The main entry point for the application.

### Functions
- `main()`: Initializes the system, enters the main application loop to handle user interactions for ticket purchasing, and shuts down when the user chooses to exit.
