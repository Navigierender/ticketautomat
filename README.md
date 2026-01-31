# Ticketautomat

This is a C++ project for a university first-semester computer science exam. It simulates a ticket vending machine for a tram system.

## Project Status

The project has a solid and modular structure but is not yet complete. The remaining tasks involve fixing critical bugs that prevent compilation and implementing the final pieces of core logic.

## To-Do List

### 1. Critical Bug Fixes (Highest Priority)

- [ ] **Fix Linker Error in `ioUtil`:**
  - **File:** `src/ioUtil.cpp`
  - **Task:** The function names `valInStrict` do not match the declarations in `src/ioUtil.h` (`strValInStrict` and `intValInStrict`). Rename the functions in the `.cpp` file to match the `.h` file.

- [ ] **Fix Runtime Crash in `tramUtil`:**
  - **File:** `src/tramUtil.cpp`
  - **Task:** In the `getTram` function, do not use the `tram_id` as a direct vector index. Instead, loop through the `trams` vector and return the tram where `tram.tram_number` matches the `tram_id` parameter.

- [ ] **Fix `change` Struct Definition and Usage:**
  - **Files:** `src/moneyUtil.h` and `src/main.cpp`
  - **Task:** The `struct change` in `moneyUtil.h` has confusing member names (`v17`, etc.) and a different number of members than what is being used to initialize it in `main.cpp`.
    - **Recommendation:** Redefine the struct with clear names (e.g., `euros_2`, `euros_1`, `cents_50`, etc.).
    - Ensure the number of members in the definition matches the number of values used for initialization in `main.cpp`.

### 2. New Features & Logic Implementation

- [ ] **Implement Payment Logic:**
  - **File:** `src/orchestrator.cpp`
  - **Function:** `finalizeOrSkip()`
  - **Task:** This function should prompt the user to enter money, calculate the total entered, and determine if it's enough to cover the `total_price`.

- [ ] **Implement Change Calculation:**
  - **File:** `src/moneyUtil.cpp`
  - **Function:** Create a new function, e.g., `calculateChange()`.
  - **Task:** This function will take the total price and the money paid as input. It should calculate the change to be returned and which coins/notes to use. Update the machine's available money supply.

- [ ] **Implement "Continue or Exit" Prompt:**
  - **File:** `src/orchestrator.cpp`
  - **Function:** `reqContinue()`
  - **Task:** This function should ask the user if they want to perform another transaction or exit the program.
