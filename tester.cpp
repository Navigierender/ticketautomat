#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "tramUtil.h"
#include "orchestrator.h"

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.is_open();
}

void runTest(const std::string& testName, bool (*testFunc)()) {
    std::cout << "Running test: " << testName << "..." << std::endl;
    if (testFunc()) {
        std::cout << "Test PASSED: " << testName << std::endl;
    } else {
        std::cout << "Test FAILED: " << testName << std::endl;
    }
    std::cout << std::endl;
}

bool testGetStationDistance() {
    if (!fileExists("tramUtil.h")) {
        std::cerr << "Error: tramUtil.h not found, skipping testGetStationDistance." << std::endl;
        return false;
    }

    tramLine testTram;
    testTram.stations = {"StationA", "StationB", "StationC", "StationD"};
    testTram.station_price = 10;
    testTram.tram_number = 1;

    std::vector<std::string> stations1 = {"StationA", "StationC"};
    if (TramUtil::getStationDistance(&testTram, stations1) != 2) return false;

    std::vector<std::string> stations2 = {"StationC", "StationA"};
    if (TramUtil::getStationDistance(&testTram, stations2) != 2) return false;

    std::vector<std::string> stations3 = {"StationB", "StationB"};
    if (TramUtil::getStationDistance(&testTram, stations3) != 0) return false;
    
    return true;
}

bool testFetchRoutePrice() {
    if (!fileExists("orchestrator.h")) {
        std::cerr << "Error: orchestrator.h not found, skipping testFetchRoutePrice." << std::endl;
        return false;
    }

    tramLine testTram;
    testTram.stations = {"S1", "S2", "S3", "S4", "S5"};
    testTram.station_price = 5;
    testTram.tram_number = 10;

    //simulate custom route
    route testRoute;
    testRoute.tram_ptr = &testTram;
    testRoute.stations = {"S1", "S4"};

    if (Orst::fetchRoutePrice(testRoute.tram_ptr, testRoute.stations) != 15) return false;
    
    testRoute.stations = {"S5", "S2"};
    if (Orst::fetchRoutePrice(testRoute.tram_ptr, testRoute.stations) != 15) return false;

    return true;
}

int main() {
    std::cout << "Starting project tests..." << std::endl << std::endl;

    runTest("TramUtil::getStationDistance", testGetStationDistance);
    runTest("Orst::fetchRoutePrice", testFetchRoutePrice);

    std::cout << "All tests completed!" << std::endl;
    return 0;
}
