#include "houseEstimate.h"

/* Fits the data to a linear model from a file
 * @param filename: the name of the file to read from
 */
void houseEstimate::fitFile(std::string filename) {
    std::ifstream file(filename);
    if (!file) {
	throw std::invalid_argument("Error: File does not exist.");
    }
    std::string line;
    std::vector<double> xVec;
    std::vector<double> yVec;
    xVec.clear();
    yVec.clear();
    while (std::getline(file, line)) {
	std::istringstream iss(line);
	double x, y;
	iss >> x >> y;
	xVec.push_back(x);
	yVec.push_back(y);
    }
    fit(xVec, yVec);
}

/* Predicts the price of a house given the square footage
 * @return the estimated price of the house
 */
double houseEstimate::predictHouse() {
    if (fitted == false) {
	throw std::invalid_argument("Error: Model has not been fitted.");
    }
    int squareFootage;
    while (true) {
        std::cout << "Enter the square footage of the home (an integer between 100 and 200,000): ";
        std::cin >> squareFootage;
        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cerr << "Invalid input. Please enter an integer.\n";
            continue;
        }
        if (squareFootage < 100 || squareFootage > 200000) {
            std::cerr << "Error: Square footage must be between 100 and 200,000.\n";
        }
        else {
	    double price = predict(squareFootage);
            return price;
        }
    }
}
