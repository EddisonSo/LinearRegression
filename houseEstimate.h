#include "leastSquares.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>

class houseEstimate : public leastSquares {
    public:
	void fitFile(std::string filename);
	double predictHouse();
};
