# Project Modules Documentation

This document provides concise technical descriptions of the project's `src` modules.

## Module: `errorHandler`
**Files:** `errorHandler.h`, `errorHandler.cpp`
**Purpose:** Manages critical program errors: initializes external error definitions, logs messages, and facilitates controlled termination with specific exit codes.
**Key Functions:**
*   `stopAndShowErrors(int id)`: Terminates program; displays all logged errors and `id`.
*   `initErrList(string errorlist_dir)`: Loads `_ID#description` errors from `errorlist_dir`.
*   `Log(int id, bool is_external)`: Appends an error message (internal or external `id`) to an internal history.
*   `stopAndLog(int id, bool is_external)`: Logs an error and calls `stopAndShowErrors(id)`.

## Module: `ioUtil`
**Files:** `ioUtil.h`, `ioUtil.cpp`
**Purpose:** Handles terminal I/O, console state management, and strict input validation.
**Key Functions:**
*   `dependencyCheck()`: Verifies `uiUtil.h` header availability; exits on failure (error 400).
*   `clearConsole()`: Clears terminal screen using ANSI escape codes.
*   `strValInStrict(string msg, string wrng_msg, vector<string> valid)`: Prompts for string input; validates against `valid` vector.
*   `intValInStrict(string msg, string wrng_msg, vector<int> valid)`: Prompts for integer input; validates against `valid` vector.
*   `valAboveOrZero(string msg, string wrng_msg, int goal)`: Prompts for integer input; validates `val >= goal || val == 0`.

## Module: `moneyUtil`
**Files:** `moneyUtil.h`, `moneyUtil.cpp`
**Purpose:** Provides utilities for managing currency denominations (`change` struct) and calculating change.
**Key Functions:**
*   `changeOutPossible(int amount, change& reservoir)`: Checks if `amount` can be dispensed from `reservoir`.
*   `processChangeOut(int amount, change& reservoir)`: Dispenses `amount` from `reservoir`; returns dispensed `change` struct.
*   `changeToVector(const change& c)`: Converts `change` struct to `vector<int>` (denomination counts).

## Module: `orchestrator`
**Files:** `orchestrator.h`, `orchestrator.cpp`
**Purpose:** Coordinates application flow: user interaction, data processing, and state transitions for ticket purchases. Integrates `tramUtil`, `uiUtil`, and `moneyUtil`.
**Key Functions:**
*   `dependencyChecks()`: Executes `IoUtil` and `UiUtil` dependency checks.
*   `reqTramSelec(const vector<tramLine>& all_trams, ...)`: Prompts for tram line selection; returns `tramLine*`.
*   `reqStationsSelect(string title_stdec0, ..., const tramLine* tramline_ptr, ...)`: Prompts for start/end stations; returns `vector<string>`.
*   `fetchRoutePrice(const tramLine* tram_ptr, const vector<string>& stations)`: Calculates route price.
*   `reqContinue(string msg, int min_width)`: Prompts user to continue/exit.
*   `finalizeOrSkip(const route& sel_route, change& reservoir, ...)`: Handles final purchase steps: money input, change calculation, and dispensing.

## Module: `tramUtil`
**Files:** `tramUtil.h`, `tramUtil.cpp`
**Purpose:** Manages tram line data lifecycle: loading from `.tram` files, querying, and distance calculation. Defines `tramLine` and `route` data structures.
**Key Functions:**
*   `loadTrams(string data_dir)`: Parses `.tram` files from `data_dir` into `vector<tramLine>`. Exits on missing `data_dir` (error 100) or invalid file format (error 102).
*   `getTramINTs(const vector<tramLine>* tram_lines)`: Extracts `tram_number`s to `vector<int>`.
*   `getTram(const std::vector<tramLine>& all_trams, int choice)`: Retrieves `tramLine` by `tram_number`; exits if not found (error 105).
*   `getStationDistance(const tramLine* tram, vector<string> prov_stations)`: Calculates station count between two stations on a `tramLine`; exits if station not found (error 104).

## Module: `uiUtil`
**Files:** `uiUtil.h`, `uiUtil.cpp`
**Purpose:** Provides UI rendering utilities, including ANSI text formatting and ASCII box drawing.
**Key Functions:**
*   `dependencyCheck()`: Verifies `ioUtil.h` header availability; exits on failure (error 300).
*   `convertIntVecToStr(const vector<int>& ints)`: Converts `vector<int>` to `vector<string>`.
*   `repeatUTF8string(int count, string input)`: Repeats `input` `count` times.
*   `drawBox(string title, vector<string> msg, int min_width)`: Renders an ASCII box with `title` and `msg` content.
*   `format` struct: Static members for ANSI escape codes (e.g., `format::RED`, `format::BOLD`, `format::up(int n)`).