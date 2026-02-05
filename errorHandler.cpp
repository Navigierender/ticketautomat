#include "errorHandler.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <filesystem>

using namespace std;



namespace {
    vector<err_element> extern_errlist;
    vector<string> logged_errors; 

    const vector<err_element> intern_errlist = {
        err_element(1, "could not load extern error-sheet"),
        err_element(2, "external error-sheet contains invalid format or non-numeric ID")
    };

    string fetchError(int id, bool use_extern) {
        const vector<err_element>& target_list = use_extern ? extern_errlist : intern_errlist;

        for (const auto& err : target_list) {
            if (err.id == id) return err.desc;
        }
        return "Error " + to_string(id) + ": cannot read error description...\n(probable causes: external error list could not be read, or error has an invalid ID)";
    }

    string findErrFile() {
        for (const auto& entry : filesystem::directory_iterator(".")) {
            if (entry.is_regular_file() && entry.path().extension() == ".err")
                return entry.path().string();
        }
        return "";
    }

    void parseErrLine(const string& line) {
        if (line.empty() || line[0] != '_') return;
        size_t hash_pos = line.find('#');
        if (hash_pos == string::npos) ErrLogger::stopAndLog(2, false);

        string id_str = line.substr(1, hash_pos - 1);
        for (char c : id_str) if (!isdigit(c)) ErrLogger::stopAndLog(2, false);

        if (id_str.empty()) ErrLogger::stopAndLog(2, false);
        extern_errlist.push_back(err_element(stoi(id_str), line.substr(hash_pos + 1)));
    }
}

namespace ErrLogger {
    void stopAndShowErrors(int id) {
        if (logged_errors.empty()) exit(0);

        cout << "\n\nCRITICAL STOP: following errors occurred:\n";
        for (const string& err : logged_errors) {
            cout << "- " << err << "\n";
        }

        exit(id);
    }

    void initErrList() {
        string path = findErrFile();
        if (path.empty()) return Log(1, false);

        ifstream file(path);
        if (!file.is_open()) return Log(1, false);

        string line;
        while (getline(file, line)) parseErrLine(line);
        file.close();
    }

    void Log(int id, bool is_external) {
        string msg = fetchError(id, is_external);
        logged_errors.push_back(msg);
    }

    void stopAndLog(int id, bool is_external) {
        Log(id, is_external);
        stopAndShowErrors(id);
    }
}
