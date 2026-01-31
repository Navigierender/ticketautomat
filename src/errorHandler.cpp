#include "errorHandler.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;



namespace {
    vector<err_element> extern_errlist;
    vector<string> logged_errors; 
    string saved_dir = "";

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

    void initErrList(string errorlist_dir) {
        saved_dir = errorlist_dir;
        ifstream file(errorlist_dir);
        if (!file.is_open()) {
            stopAndLog(1, false);
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty() || line[0] != '_') continue;

            size_t hash_pos = line.find('#');
            if (hash_pos == string::npos) {
                stopAndLog(2, false);
                return;
            }

            string id_str = line.substr(1, hash_pos - 1);
            string description = line.substr(hash_pos + 1);

            bool is_num = !id_str.empty();
            for(char c : id_str) if(!isdigit(c)) is_num = false;

            if (!is_num) {
                stopAndLog(2, false);
                return;
            }

            extern_errlist.push_back(err_element(stoi(id_str), description));
        }
        file.close();
    }

    void Log(int id, bool is_external) {
        string msg = fetchError(id, is_external);
        if (!is_external && id == 1) msg += " (Path: " + saved_dir + ")";
        
        logged_errors.push_back(msg);
    }

    void stopAndLog(int id, bool is_external) {
        Log(id, is_external);
        stopAndShowErrors(id);
    }
}
