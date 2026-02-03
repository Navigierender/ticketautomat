# Ticketautomat

This is a simple ticket vending machine for a tram system.

## How to build

To build the project, simply run the `build.sh` script:

```bash
bash build.sh
```

This will compile the project and create an executable named `tam` in the root directory.

## File descriptions

*   `main.cpp`: The main entry point of the program.
*   `errorHandler.h`, `errorHandler.cpp`: Manages critical program errors.
*   `ioUtil.h`, `ioUtil.cpp`: Handles terminal I/O and input validation.
*   `moneyUtil.h`, `moneyUtil.cpp`: Provides utilities for managing currency and calculating change.
*   `orchestrator.h`, `orchestrator.cpp`: Coordinates the application flow.
*   `tramUtil.h`, `tramUtil.cpp`: Manages tram line data.
*   `uiUtil.h`, `uiUtil.cpp`: Provides UI rendering utilities.
*   `*.tram`: Tram data files.
*   `*.err`: Error list file.
*   `build.sh`: The build script.
*   `README.md`: This file.