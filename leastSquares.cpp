#include "leastSquares.h"

/* Constructor for the leastSquares class 
 */
leastSquares::leastSquares() {
    fitted = false;
    R2 = 0;
    m = 0;
    c = 0;
    mse = 0;
    t_stat_m = 0;
    t_stat_c = 0;
    p_value_m = 0;
    p_value_c = 0;
}

/* Calculates the sum of squares of the residuals
 * @param y: the y values of the data
 * @param x: the x values of the data
 * @return the sum of squares of the residuals
 */
double leastSquares::calculateSSres(std::vector<double> y, std::vector<double> x) {
    if (!fitted) {
        throw std::runtime_error("Model not fitted yet");
    }

    double ssres = 0;
    for (int i = 0; i < y.size(); i++) {
        ssres += (predict(x[i]) - y[i]) * (predict(x[i]) - y[i]);
    }
    return ssres;
}

/* Calculates the total sum of squares
 * @param y: the y values of the data
 * @return the total sum of squares
 */
double leastSquares::calculateSStot(std::vector<double> y) {
    if (!fitted) {
        throw std::runtime_error("Model not fitted yet");
    }

    double mean = 0;
    for (const double& yi : y) {
        mean += yi;
    }
    mean /= y.size();

    double sstot = 0;
    for (const double& yi : y) {
        sstot += (yi - mean) * (yi - mean);
    }
    return sstot;
}

/* Calculates the R^2 value of the model
 * @param y: the y values of the data
 * @param x: the x values of the data
 */
void leastSquares::calculateRSquared(std::vector<double> y, std::vector<double> x) {
    if (!fitted) {
        throw std::runtime_error("Model not fitted yet");
    }

    double ssres = calculateSSres(y, x);
    double sstot = calculateSStot(y);
    R2 = 1 - ssres / sstot;
}

/* Calculates the mean squared error of the model
 * @param y: the y values of the data
 * @param x: the x values of the data
 */
void leastSquares::calculateMSE(std::vector<double> y, std::vector<double> x) {
    if (!fitted) {
        throw std::runtime_error("Model not fitted yet");
    }

    double ssres = calculateSSres(y, x);
    mse = ssres / y.size();
}

/* Calculates the t-statistics and p-values for the slope and intercept
 * @param x: the x values of the data
 * @param y: the y values of the data
 */
void leastSquares::calculateTTests(std::vector<double> x, std::vector<double> y) {
    if (!fitted) {
        throw std::runtime_error("Model not fitted yet");
    }

    int n = x.size();
    double ssres = calculateSSres(y, x);
    double s2 = ssres / (n - 2); 
    double sum_x = 0, sum_x_squared = 0;
    for (double xi : x) {
        sum_x += xi;
        sum_x_squared += xi * xi;
    }
    double mean_x = sum_x / n;

    double SE_m = std::sqrt(s2 / (sum_x_squared - n * mean_x * mean_x));
    double SE_c = std::sqrt(s2 * (1.0 / n + mean_x * mean_x / (sum_x_squared - n * mean_x * mean_x)));

    t_stat_m = m / SE_m;
    t_stat_c = c / SE_c;

    p_value_m = 2 * (1 - std::erf(std::abs(t_stat_m) / std::sqrt(2)));
    p_value_c = 2 * (1 - std::erf(std::abs(t_stat_c) / std::sqrt(2)));
}

/* Fits the data to a linear model
 * @param x: the x values of the data
 * @param y: the y values of the data
 */
void leastSquares::fit(std::vector<double> x, std::vector<double> y) {
    if (x.size() != y.size()) {
        std::cout << "x and y must be of the same size" << std::endl;
        return;
    }
    int n = x.size();
    Matrix Xm(n, 2);
    Matrix ym(n, 1, y);

    for (int i = 0; i < n; i++) {
        Xm.setElem(i, 0, x[i]);
        Xm.setElem(i, 1, 1);
    }

    Matrix XTX = Xm.transpose() * Xm;
    Matrix XTXi = XTX.inverse();
    Matrix b = XTXi * Xm.transpose() * ym;

    m = b.getElem(0, 0);
    c = b.getElem(1, 0);
    fitted = true;

    calculateRSquared(y, x);
    calculateMSE(y, x);
    calculateTTests(x, y);

    std::cout << "Least Squares Regression Model: " << std::endl;
    std::cout << "Model: " << n << "x + " << c << std::endl;
    std::cout << "R^2: " << R2 << std::endl;
}

/* Predicts the y values of the data
 * @param x: the x values of the data
 * @return the predicted y values
 */
std::vector<double> leastSquares::predict(std::vector<double> x) {
    if (!fitted) {
        throw std::runtime_error("Model not fitted yet");
    }

    std::vector<double> yHat;
    for (const double& xi : x) {
        yHat.push_back(predict(xi));
    }
    return yHat;
}

/* Predicts the y value of a single x value
 * @param x: the x value to predict
 * @return the predicted y value
 */
double leastSquares::predict(double x) {
    if (!fitted) {
        throw std::runtime_error("Model not fitted yet");
    }
    return m * x + c;
}

/* Prints the statistics of the model
 */
void leastSquares::getStats() {
    if (!fitted) {
        std::cout << "Model not fitted yet" << std::endl;
        return;
    }

    std::cout << "\nModel Statistics:" << std::endl;
    std::cout << "Equation: " << m << "x + " << c << std::endl;
    std::cout << "R^2: " << R2 << std::endl;
    std::cout << "MSE: " << mse << std::endl;
    std::cout << "Slope (m): t-statistic = " << t_stat_m << ", p-value = " << p_value_m << std::endl;
    std::cout << "Intercept (c): t-statistic = " << t_stat_c << ", p-value = " << p_value_c << std::endl;
}
