#include <iostream>
#include "ttc.hpp"
#include <cmath>

bool testTTC (const SensorData&data, double expected) {
    double actual = calculateTTC(data);
    if (std::abs (actual - expected ) < 0.000001)
    {
        return true;
    }
    std::cout << " Test failed! Expected : " << expected << ", Actual " << actual << ", \n";
    return false;
}

int main () {
    int passed = 0;
    int total = 0;

    // Test 1
    total++;
    if (testTTC({20.0, 10.0},2.0)) {
        passed++;
        std ::cout << "Test 1 passed!\n";
    }

    // Test 2
    total++;
    if (testTTC({30.0 ,5.0},6.0)) {
        passed++;
        std::cout << "Test 2 passed!\n";
    }
    
    // Test 3
    total++;
    if (testTTC({10.0, 5.0},2.0)) {
        passed++;
        std::cout << "Test 3 passed!\n";
    }

    std::cout << "\nPassed: " << passed << "/" << total << "\n";

    return (passed  == total) ? 0 : 1;
}