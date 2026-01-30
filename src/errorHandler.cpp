#include "ErrorHandler.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;

struct err_element {
    int id;
    string desc;

    err_element(int _id, string _desc) : id(_id), desc(_desc) {}
};

namespace {
    vector<err_element> extern_errlist;
    vector<string> logged_errors; 
    string saved_dir = "";

    const vector<err_element> intern_errlist = {
        err_element(1, "could not load extern error-sheet")
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
            Log(1, false); 
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string id_str, description;

            if (getline(ss, id_str, ':') && getline(ss, description)) {
                // Wir fangen nur die spezifischen stoi-Fehler ab
                try {
                    int parsed_id = stoi(id_str);
                    extern_errlist.push_back(err_element(parsed_id, description));
                } catch (const invalid_argument&) {
                    continue; 
                } catch (const out_of_range&) {
                    continue;
                }
            }
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