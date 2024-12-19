#pragma once
#include "matrix.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

class leastSquares {
    protected:
	bool fitted;
    private:
        double R2;
        double m;
        double c;
        double mse;
        double t_stat_m;
        double t_stat_c;
        double p_value_m;
        double p_value_c;

        void calculateRSquared(std::vector<double> y, std::vector<double> x);
        double calculateSSres(std::vector<double> y, std::vector<double> x);
        double calculateSStot(std::vector<double> y);
        void calculateMSE(std::vector<double> y, std::vector<double> x);
        void calculateTTests(std::vector<double> x, std::vector<double> y);

    public:
        leastSquares();
        void fit(std::vector<double> x, std::vector<double> y);
        std::vector<double> predict(std::vector<double> x);
        double predict(double x);
        void getStats();
};

