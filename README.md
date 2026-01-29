# Ticketautomat (Ticket Vending Machine)

## Project Description
This project implements a console-based ticket vending machine for a tram system. It allows users to select tram lines, specify start and end stations, calculates the fare, processes payment, and provides change. The system is designed to be interactive and user-friendly within a command-line interface.

## Features
*   **Tram Line Selection:** Users can choose from available tram lines.
*   **Station Selection:** Users can specify their start and end stations for a journey on a selected tram line.
*   **Fare Calculation:** Automatically calculates the fare based on the tram line's price per station and the distance between selected stations.
*   **Payment Processing:** Handles user input for payment and validates it against the fare.
*   **Change Calculation:** Determines and provides the optimal change using a predefined set of denominations from a money reservoir.
*   **Interactive User Interface:** Provides a simple, text-based interactive interface for user input and output, including formatted boxes for displaying information.
*   **Data Loading:** Loads tram line data (tram number, price per station, stations) from external files.

## How to Build
*(Placeholder: Instructions for compiling the C++ source code will go here. This typically involves a C++ compiler like g++.)*
Example: `g++ -o tam src/*.cpp -std=c++17`

## How to Run
*(Placeholder: Instructions for running the compiled executable will go here.)*
Example: `./tam`

## Project Structure Highlights
*   **`main.cpp`**: Contains the main application logic, orchestrating user interaction, tram selection, fare calculation, and payment processing.
*   **`io.h`/`io.cpp`**: Handles robust user input validation for various scenarios (strict string matching, range checking, etc.).
*   **`monCalc.h`/`monCalc.cpp`**: Manages monetary calculations, including converting integer values to change denominations, checking for sufficient change, and calculating optimal change.
*   **`tramManager.h`/`tramManager.cpp`**: Manages tram line data, including loading tram configurations from files, retrieving specific tram lines, and calculating distances between stations.
*   **`uiFormat.h`/`uiFormat.cpp`**: Provides utility functions for formatting console output, such as drawing ASCII boxes and repeating UTF-8 strings for visual presentation.
*   **`tram_data/`**: Directory containing data files for different tram lines.

## Authors
GdP Abschlussprojekt Team