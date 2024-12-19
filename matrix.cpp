#include "matrix.h"

/*
 * Matrix Constructor
 */
Matrix::Matrix() : rows(1), cols(1) {
    data = std::shared_ptr<double[]>(new double[1]);
}

/*
 * Matrix Constructor
 * @param rows Number of rows
 * @param cols Number of columns
 */
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data = std::shared_ptr<double[]>(new double[rows * cols]);
}

/*
 * Print the matrix
 */
void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
	for (int j = 0; j < cols; j++) {
	    std::cout << data[i * cols + j] << " ";
	}
	std::cout << std::endl;
    }
}

/*
 * Matrix Constructor
 * @param rows Number of rows
 * @param cols Number of columns
 * @param data Data to be stored in the matrix
 */
Matrix::Matrix(int rows, int cols, std::vector<double> data) : rows(rows), cols(cols) {
    this->data = std::shared_ptr<double[]>(new double[rows * cols]);
    for (int i = 0; i < rows * cols; i++) {
	this->data[i] = data[i];
    }
}

/*
 * Gets an element from the Matrix
 * @param i Row index
 * @param j Column index
 * @return Element at (i, j)
 */
double Matrix::getElem(int i, int j) const {
    return data[i * cols + j];
}

/*
 * Sets an element in the Matrix
 * @param i Row index
 * @param j Column index
 * @param elem Element to be set
 */
void Matrix::setElem(int i, int j, double elem) const {
    data[i*cols + j] = elem;
}

/*
 * Matrix Constructor
 * @param rows Number of rows
 * @param cols Number of columns
 * @param data Data to be stored in the matrix
 */
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = std::shared_ptr<double[]>(new double[rows * cols]);
    for (int i = 0; i < rows * cols; i++) {
	data[i] = other.data[i];
    }
}

/*
 * Matrix Constructor
 * @param other Matrix to be copied
 */
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
	return *this;
    }
    this->rows = other.rows;
    this->cols = other.cols;
    this->data = other.data;
    return *this;
}

/*
 * Matrix multiplication
 * @param other Matrix to be multiplied
 * @return Result of the matrix multiplication
 */
Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
	for (int j = 0; j < other.cols; j++) {
	    for (int k = 0; k < cols; k++) {
		result.data[i * other.cols + j] += data[i * cols + k] * other.data[k * other.cols + j];
	    }
	}
    }
    return result;
}

/*
 * Matrix addition
 * @param other Matrix to be added
 * @return Result of the matrix addition
 */
Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
	for (int j = 0; j < cols; j++) {
	    result.data[j * rows + i] = data[i * cols + j];
	}
    }
    return result;
}

/*
 * Matrix inversion
 * @return Inverse of the matrix
 */
Matrix Matrix::inverse() const {
    int n = rows;
    Matrix result(n, n);
    Matrix augmented(n, 2 * n);

    //Create augmented matrix
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	    augmented.data[i * (2 * n) + j] = getElem(i, j);
	    augmented.data[i * (2 * n) + (j + n)] = (i == j) ? 1.0 : 0.0; // Identity matrix
	}
    }

    //Gaussian elimination
    for (int i = 0; i < n; i++) {
	double pivot = augmented.data[i * (2 * n) + i];

	for (int j = 0; j < 2 * n; j++) {
	    augmented.data[i * (2 * n) + j] /= pivot;
	}

	for (int k = 0; k < n; k++) {
	    if (k == i) continue; 
	    double factor = augmented.data[k * (2 * n) + i];
	    for (int j = 0; j < 2 * n; j++) {
		augmented.data[k * (2 * n) + j] -= factor * augmented.data[i * (2 * n) + j];
	    }
	}
    }

    //Copy result
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	    result.data[i * n + j] = augmented.data[i * (2 * n) + (j + n)];
	}
    }

    return result;
}
