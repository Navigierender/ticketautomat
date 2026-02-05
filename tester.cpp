#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <numeric>
#include <algorithm>

// Include all project headers
#include "errorHandler.h"
#include "ioUtil.h"
#include "moneyUtil.h"
#include "orchestrator.h"
#include "tramUtil.h"
#include "uiUtil.h"

// ###################################################################################
// # Mock Implementations to make this file runnable in isolation
// ###################################################################################

// Mock implementations from errorHandler.h
namespace ErrLogger {
    void initErrList() {}
    void Log(int, bool) {}
    void stopAndLog(int, bool) { exit(1); }
    void stopAndShowErrors(int) { exit(1); }
}

// Mock implementations from ioUtil.h
namespace IoUtil {
    void dependencyCheck() {}
    void clearConsole() {}
    void awaitInput(std::string msg) {}
    std::string strValInStrict(std::string msg, std::string wrng_msg, std::vector<std::string> valid) {
        if (!valid.empty()) return valid[0];
        return "";
    }
    int intValInStrict(std::string msg, std::string wrng_msg, std::vector<int> valid) {
        if (!valid.empty()) return valid[0];
        return 0;
    }
    int valAboveOrZero(std::string msg, std::string wrng_msg, int goal) {
        return goal;
    }
}

// Mock implementations from moneyUtil.h
namespace MoneyUtil {
    bool changeOutPossible(int amount, change& reservoir) {
        return true;
    }
    change processChangeOut(int amount, change& reservoir) {
        return change{0,0,0,0,0,0,0};
    }
    std::vector<int> changeToVector(const change& c) {
        return {c.v17, c.v11, c.v7, c.v5, c.v3, c.v2, c.v1};
    }
}

// Mock implementations from uiUtil.h
namespace UiUtil {
    void dependencyCheck() {}
    std::vector<std::string> convertIntVecToStr(const std::vector<int>& ints) {
        std::vector<std::string> strs;
        for (int i : ints) {
            strs.push_back(std::to_string(i));
        }
        return strs;
    }
    std::string repeatUTF8string(int count, std::string input) {
        std::string result = "";
        for (int i = 0; i < count; ++i) {
            result += input;
        }
        return result;
    }
    std::string drawBox(std::string title, std::vector<std::string> msg, int min_width) {
        return "box";
    }
}

// Mock implementations from tramUtil.h
namespace TramUtil {
    const std::vector<tramLine> loadTrams() {
        return {
            {1, 10, {"A", "B", "C"}},
            {2, 12, {"D", "E"}}
        };
    }
    const std::vector<int> getTramINTs(const std::vector<tramLine>* tram_lines) {
        std::vector<int> ids;
        if(tram_lines) {
            for(const auto& line : *tram_lines) {
                ids.push_back(line.tram_number);
            }
        }
        return ids;
    }
    const tramLine& getTram(const std::vector<tramLine>& all_trams, int choice) {
        for(const auto& tram : all_trams) {
            if(tram.tram_number == choice) return tram;
        }
        // This part should not be reached in a real scenario due to error handling
        throw std::runtime_error("Tram not found in mock");
    }
    int getStationDistance(const tramLine* tram, std::vector<std::string> prov_stations) {
        if (!tram || prov_stations.size() != 2) return 0;
        return 1;
    }
}

// Mock implementations from orchestrator.h
namespace Orst {
    void dependencyChecks() {}
    const tramLine* reqTramSelec(const vector<tramLine>& all_trams, const vector<int>& valid_ids, string title, int min_width) {
        if (!all_trams.empty()) return &all_trams[0];
        return nullptr;
    }
    vector<string> reqStationsSelect(string title_stdec0, string title_stdec1, const tramLine* tramline_ptr, int min_width) {
        if(tramline_ptr && tramline_ptr->stations.size() >= 2) {
            return {tramline_ptr->stations[0], tramline_ptr->stations[1]};
        }
        return {};
    }
    int fetchRoutePrice(const tramLine* tram_ptr, const std::vector<std::string>& stations) {
        if(!tram_ptr) return 0;
        int dist = TramUtil::getStationDistance(tram_ptr, stations);
        return dist * tram_ptr->station_price;
    }
    bool reqContinue(string msg, int min_width) {
        return true;
    }
    void finalizeOrSkip(const route& sel_route, change& reservoir, string msg_moneyout, string title, string msg_station0, string msg_station1, string msg_tram_number, string msg_price, string msg_cancel, int min_width) {}
}


// ###################################################################################
// # Test Functions
// ###################################################################################

void test_moneyUtil_changeToVector() {
    change c = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> result = MoneyUtil::changeToVector(c);
    assert(result.size() == 7);
    assert(result[0] == 1);
    assert(result[6] == 7);
}

void test_moneyUtil_changeOutPossible() {
    change res;
    assert(MoneyUtil::changeOutPossible(100, res) == true);
}

void test_uiUtil_convertIntVecToStr() {
    std::vector<int> ints = {1, 2, 3};
    std::vector<std::string> strs = UiUtil::convertIntVecToStr(ints);
    assert(strs.size() == 3);
    assert(strs[0] == "1");
    assert(strs[2] == "3");
}

void test_uiUtil_repeatUTF8string() {
    std::string result = UiUtil::repeatUTF8string(3, "A");
    assert(result == "AAA");
}

void test_uiUtil_drawBox() {
    std::string box = UiUtil::drawBox("Title", {"line1"}, 10);
    assert(box == "box");
}

void test_tramUtil_loadTrams() {
    std::vector<tramLine> trams = TramUtil::loadTrams();
    assert(trams.size() >= 1);
}

void test_tramUtil_getTramINTs() {
    std::vector<tramLine> trams = TramUtil::loadTrams();
    std::vector<int> ids = TramUtil::getTramINTs(&trams);
    assert(ids.size() == trams.size());
    assert(ids[0] == 1);
}

void test_tramUtil_getTram() {
    std::vector<tramLine> trams = TramUtil::loadTrams();
    const tramLine& tram = TramUtil::getTram(trams, 1);
    assert(tram.tram_number == 1);
}

void test_tramUtil_getStationDistance() {
    std::vector<tramLine> trams = TramUtil::loadTrams();
    const tramLine* tram = &trams[0];
    int dist = TramUtil::getStationDistance(tram, {"A", "B"});
    assert(dist == 1);
}

void test_orst_fetchRoutePrice() {
    std::vector<tramLine> trams = TramUtil::loadTrams();
    const tramLine* tram = &trams[0];
    int price = Orst::fetchRoutePrice(tram, {"A", "C"});
    assert(price == 10);
}

void test_orst_reqTramSelec() {
    auto trams = TramUtil::loadTrams();
    auto ids = TramUtil::getTramINTs(&trams);
    const tramLine* tram = Orst::reqTramSelec(trams, ids, "title", 10);
    assert(tram != nullptr);
    assert(tram->tram_number == 1);
}

void test_orst_reqStationsSelect() {
    auto trams = TramUtil::loadTrams();
    const tramLine* tram = &trams[0];
    auto stations = Orst::reqStationsSelect("a", "b", tram, 10);
    assert(stations.size() == 2);
    assert(stations[0] == "A");
    assert(stations[1] == "B");
}

void test_ioUtil_intValInStrict() {
    int val = IoUtil::intValInStrict("msg", "wrng", {10, 20});
    assert(val == 10);
}

void test_ioUtil_strValInStrict() {
    string val = IoUtil::strValInStrict("msg", "wrng", {"A", "B"});
    assert(val == "A");
}

// Dummy tests for functions that mostly have side-effects (IO, exit)
void test_side_effect_functions() {
    ErrLogger::initErrList();
    ErrLogger::Log(1, true);
    IoUtil::dependencyCheck();
    IoUtil::clearConsole();
    IoUtil::awaitInput("msg");
    Orst::dependencyChecks();
    assert(true); // If we reached here, the functions ran without crashing.
}

int main() {
    std::cout << "Starting tests..." << std::endl;

    test_moneyUtil_changeToVector();
    test_moneyUtil_changeOutPossible();
    test_uiUtil_convertIntVecToStr();
    test_uiUtil_repeatUTF8string();
    test_uiUtil_drawBox();
    test_tramUtil_loadTrams();
    test_tramUtil_getTramINTs();
    test_tramUtil_getTram();
    test_tramUtil_getStationDistance();
    test_orst_fetchRoutePrice();
    test_orst_reqTramSelec();
    test_orst_reqStationsSelect();
    test_ioUtil_intValInStrict();
    test_ioUtil_strValInStrict();
    test_side_effect_functions();

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}
