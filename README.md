# Ticketautomat DOC

## errorHandler
Handles error logging and program termination outside of user responsibility

### Functions
- `ErrLogger::stopAndShowErrors(int id)`: prints all logged errors and terminates the program
- `ErrLogger::initErrList()`: loads the error list from a `.err` file
- `ErrLogger::Log(int id, bool is_external)`: adds an error to the internal history without programm termination
- `ErrLogger::stopAndLog(int id, bool is_external)`: logs a final error and triggers immediate programm termination

## ioUtil
Provides input/output utility functions.

### Functions
- `IoUtil::dependencyCheck()`: checks for necessary external dependencies and terminates on failure using the `errLogger` module
- `IoUtil::clearConsole()`: clears the console screen.
- `IoUtil::awaitInput(string msg)`: pauses execution and waits for user input
- `IoUtil::strValInStrict(string msg, string wrng_msg, vector<string> valid)`: validates string input against a list of provided valid elements
- `IoUtil::intValInStrict(string msg, string wrng_msg, vector<int> valid)`: validates integer input against a list of provided valid elements
- `IoUtil::valAboveOrZero(string msg, string wrng_msg, int goal)`: validates that an integer input is greater than or equal to a provided specified value

## moneyUtil
Manages currency and change calculations.

### Functions
- `MoneyUtil::changeOutPossible(int amount, change& reservoir)`: checks if change can be made for a given amount
- `MoneyUtil::processChangeOut(int amount, change& reservoir)`: processes a change transaction, updating the money reservoir using a reference to the reservoir
- `MoneyUtil::changeToVector(const change& c)`: converts a `change` struct to a vector of integers

## orchestrator
Coordinates the main application logic and user flow.

### Functions
- `Orst::dependencyChecks()`: performs initial dependency checks for the orchestrator (utilized in the `errLogger` module)
- `Orst::reqTramSelec(...)`: prompts the user to select a tram line
- `Orst::reqStationsSelect(...)`: prompts the user to select start and end stations of a tram line
- `Orst::fetchRoutePrice(...)`: calculates the price for a selected route
- `Orst::reqContinue(...)`: asks the user if they want to perform another loop of the main function in `main.cpp`
- `Orst::finalizeOrSkip(...)`: handles the final ticket purchase and payment confirmation

## tramUtil
Handles loading and managing tram line data.

### Functions
- `TramUtil::loadTrams()`: loads tram data from `.tram` files in the projects directory
- `TramUtil::getTramINTs(const vector<tramLine>* tram_lines)`: extracts the tram line numbers from a vector of tram lines
- `TramUtil::getTram(const vector<tramLine>& all_trams, int choice)`: retrieves a specific tram line by its number
- `TramUtil::getStationDistance(const tramLine* tram, vector<string> prov_stations)`: calculates the distance in stations between two stations on a tram line

## uiUtil
Provides utilities for creating text-based user interfaces.

### Functions
- `UiUtil::dependencyCheck()`: checks for necessary external dependencies and terminates on failure utilizing the `errLogger` module
- `UiUtil::convertIntVecToStr(const vector<int>& ints)`: converts a vector of integers to a vector of strings
- `UiUtil::repeatUTF8string(int count, string input)`: repeats a string multiple times
- `UiUtil::drawBox(string title, vector<string> msg, int min_width)`: draws a formatted box with a title and message content

## File Formats

### .err files
`.err` files contain a list of predefined error messages. They are used by the `errorHandler` module to provide consistent and descriptive error reporting within the application. Each error message is associated with a unique error ID
**Format:** `_ID#MESSAGE` (e.g., `_100#could not load 'tram_data'`). Comments indicating ID ranges are also present

### .tram files
These files store the data for individual tram lines. Each `.tram` file describes a single tram line, including its "ID", price and stations
**Format:**
- Line 1: Tram Line Name (e.g., `Linie 8`)
- Line 2: Price per station (integer, e.g., `3`)
- Subsequent Lines: Station names, one per line

## tester
Contains unit tests for the project

### Functions
- `main()`: Executes defined test cases, including `testGetStationDistance` and `testFetchRoutePrice`, and reports the results

## main
The main entry point for the application.

### Functions
- `main()`: Initializes the system, enters the main application loop to handle user interactions for ticket purchasing, and shuts down when the user chooses to exit.
It mostly just utilizes functions from the Orchestrator for code redeability.
