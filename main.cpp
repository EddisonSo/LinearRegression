#include "houseEstimate.h"
#include <iostream>

int main() {
    houseEstimate he;
    he.fitFile("housePrice.txt");
    double prediction = he.predictHouse();
    std::cout << std::endl << "Prediction = " << prediction << std::endl;
    he.getStats();

    return 0;
}

