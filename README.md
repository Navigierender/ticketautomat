# Ticketautomat (Ticket Vending Machine) - Refactoring Branch

This branch focuses on refactoring the Ticketautomat project for improved modularity and maintainability. The goal is to re-architect the system into cleaner, more testable components.

## How to Build

To compile the application, run the `build.sh` script:

```bash
./build.sh
```

This will create an executable named `tam` in the `build/` directory.

## What's Still Needed

For the application to run and be fully functional, the following key components need implementation:

*   **Tram Data Utilities (`TramUtil`):** Complete the implementation of functions for retrieving tram line details and managing tram IDs. This includes adding `TramUtil::getTram` to `tramUtil.h` and its definition to `tramUtil.cpp`.
*   **UI Utilities (`UiUtil`):** Implement the `clearConsole` function in `src/uiUtil.cpp`.
*   **Orchestration Logic (`Orst`):** Provide full implementations for `reqStationsSelect`, `fetchRoutePrice`, `reqContinue`, and `finalizeOrSkip` in `src/orchestrator.cpp`. These are currently empty stubs.
*   **Money Handling (`MoneyUtil`):** Implement all money calculation, payment processing, and change dispensing logic. The `src/moneyUtil.cpp` file is currently empty.