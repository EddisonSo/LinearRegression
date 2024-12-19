#pragma once
#include <memory>
#include <vector>
#include <iostream>

class Matrix {
    private:
	int rows, cols;
	std::shared_ptr<double[]> data;
    public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, std::vector<double> data);
	Matrix(const Matrix& other);
	void print() const;
	double getElem(int i, int j) const;
	void setElem(int i, int j, double elem) const;
	Matrix& operator=(const Matrix& other);
	Matrix operator*(const Matrix& other) const;
	Matrix transpose() const;
	Matrix inverse() const;
};

