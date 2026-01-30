#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "uiUtil.h"

#include <string>

using namespace std;

struct err_element {
    int id;
    string desc;
};

namespace ErrLogger {
    /**
     * @brief Prints all logged errors and terminates the program.
     * @param id The exit code returned to the operating system.
     */
    void stopAndShowErrors(int id);

    /**
     * @brief Loads the error list from a colon-separated file.
     * @param errorlist_dir File path to the external error sheet.
     */
    void initErrList(string errorlist_dir);

    /**
     * @brief Adds an error to the internal history without stopping.
     * @param id The error ID to look up.
     * @param is_external True for external file, false for internal backup.
     */
    void Log(int id, bool is_external);

    /**
     * @brief Logs a final error and triggers immediate shutdown.
     * @param id The error ID and final exit code.
     * @param is_external Selection of the source list.
     */
    void stopAndLog(int id, bool is_external);
}

#endif