# Ticketautomat (Ticket Vending Machine)

**_NOTE: This is a development branch focusing on refactoring the original Ticketautomat project for improved modularity and maintainability. The `src` directory represents the in-development version, and not all features are fully integrated or functional yet._**

## Project Description
This project implements a console-based ticket vending machine for a tram system. The goal of this development branch is to re-architect the original system into a more modular and maintainable codebase, enhancing separation of concerns and making future development and debugging easier. It aims to eventually allow users to select tram lines, specify start and end stations, calculate the fare, process payment, and provide change. The system is designed to be interactive and user-friendly within a command-line interface.

## Improvements over the Classical Version

This development branch aims to significantly improve upon the original `src_old_reference` implementation by focusing on key software engineering principles:

*   **Enhanced Modularity:** The code is being broken down into smaller, self-contained units (e.g., `ioUtils`, `uiUtils`, `orchestrator`, `tramManag`), each with a specific responsibility. This contrasts with the more monolithic structure of the classical version.
*   **Improved Maintainability:** With clearer separation of concerns, individual modules can be understood, debugged, and modified independently, reducing the risk of introducing bugs in other parts of the system.
*   **Easier Testability:** Modular components are inherently easier to unit test, leading to a more robust and reliable codebase.
*   **Better Scalability:** Adding new features or modifying existing logic becomes simpler and less error-prone when changes are localized to specific modules, rather than spread across a large codebase.
*   **Clearer Separation of Concerns:** Each header and source file in `src` is designed to handle a distinct aspect of the system, promoting cleaner architecture and making the project easier to navigate for new developers.

## Features

### Original System Features (from `src_old_reference`)
*   **Tram Line Selection:** Users can choose from available tram lines.
*   **Station Selection:** Users can specify their start and end stations for a journey on a selected tram line.
*   **Fare Calculation:** Automatically calculates the fare based on the tram line's price per station and the distance between selected stations.
*   **Payment Processing:** Handles user input for payment and validates it against the fare.
*   **Change Calculation:** Determines and provides the optimal change using a predefined set of denominations from a money reservoir.
*   **Interactive User Interface:** Provides a simple, text-based interactive interface for user input and output, including formatted boxes for displaying information.
*   **Data Loading:** Loads tram line data (tram number, price per station, stations) from external files.

### Current Status of `src` (Development Branch)
*   **Implemented/In Progress:**
    *   Basic project structure for modularity.
    *   `main.cpp` as the entry point and orchestrator.
    *   `orchestrator.h`/`orchestrator.cpp` for managing application flow.
    *   `ioUtils.h` for input/output utilities (basic input functionality likely present).
    *   `uiUtils.h` for user interface formatting (basic display functionality likely present).
    *   `tramManag.h` for tram data management (header is present, implementation might be partial or in progress).
    *   **Reason for this branch:** To move away from a monolithic structure towards a more segmented and maintainable architecture, improving code organization and testability.

*   **To Be Done/Integrated:**
    *   Full implementation of `tramManag.cpp` (if not already part of `orchestrator`).
    *   **Monetary Calculation (`monCalc` equivalent):** Integration or re-implementation of fare calculation, payment processing, and change calculation logic. This is a significant missing piece from the `src_old_reference`.
    *   Complete integration of all original features into the new modular structure.
    *   Robust error handling and input validation across all modules.
    *   Unit tests for individual modules.

## How to Build (Development Version)
To build the current development version in the `src` directory:
```bash
./build.sh
```
This script should compile the C++ source files and create the executable.

*(Alternatively, if `build.sh` is not set up or needs manual invocation, you might use something like: `g++ -o build/tam src/*.cpp -std=c++17`)*

## How to Run (Development Version)
After building, the executable `tam` will be located in the `build/` directory.
```bash
./build/tam
```

## Project Structure Highlights (Development Branch - `src`)
*   **`main.cpp`**: The primary entry point of the application, responsible for initializing the orchestrator and starting the main application loop.
*   **`orchestrator.h`/`orchestrator.cpp`**: Central component that coordinates interactions between different modules (UI, I/O, Tram Management). It manages the overall flow of the application.
*   **`ioUtils.h`**: Provides utility functions for handling user input and output operations, aiming for robust and validated interactions.
*   **`uiUtils.h`**: Contains functions responsible for formatting and displaying information to the console, including drawing boxes and other UI elements for a user-friendly experience.
*   **`tramManag.h`**: Defines the interface for managing tram line data, including loading configurations, retrieving tram lines, and calculating distances. (Implementation details for `.cpp` file may vary, could be integrated into orchestrator or a separate `.cpp` file).
*   **`tram_data/`**: Directory containing data files for different tram lines. (Same as original)

## Authors
GdP Abschlussprojekt Team