#pragma once
#include <vector>
#include <cmath>
#include <numeric>
#include "vector.h"



template<class T>
class Matrix {
private:
    std::vector<Vector<T>> data;
    std::pair<std::size_t, std::size_t> matrixSize;

public:
    Matrix() {}
    Matrix(const std::vector<std::vector<T>>& mat) : data(mat) {}
    Matrix(std::initializer_list<Vector<T>> init) : data(init) {}



    // Function to get the number of rows in the matrix
    std::size_t rows() const {
        return data.size();
    }

    // Function to get the number of columns in the matrix
    std::size_t cols() const {
        return data[0].size();
    }

    // Function to get the size of the vector
    std::size_t size() const {
        return data.size();
    }

    Vector<T>& operator[](std::size_t index) {
        return data[index];
    }

    const Vector<T>& operator[](std::size_t index) const {
        return data[index];
    }

    // Function to perform matrix multiplication
    Matrix<T> operator*(const Matrix<T>& other) const {
        Matrix<T> result;
        if (cols() != other.rows()) {
            std::cout << "Incompatible matrix dimensions for multiplication!" << std::endl;
            return result;
        }

        std::size_t rows = this->rows();
        std::size_t cols = other.cols();
        std::size_t common_dim = other.rows();

        result.data.resize(rows, std::vector<T>(cols, 0));

        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                for (std::size_t k = 0; k < common_dim; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    // Function to calculate the || * || 1 norm of the matrix
    T norm1() const {
        T res;
        T max = 0;
        for (int i = 0; i < rows(); i++)
        {
            res = 0;
            for (int j = 0; j < cols(); j++)
            {
                res = res + abs(this->data[j][i]);
            }
            if (max < res)
            {
                max = res;
            }
        }
        return max;
    }

    // Function to calculate the || * ||∞ norm of the matrix
    T normInf() const{
        T res;
        T max = 0;
        for (int i = 0; i < rows(); i++)
        {
            res = 0;
            for (int j = 0; j < cols(); j++)
            {
                res = res + abs(this->data[i][j]);
            }
            if (max < res)
            {
                max = res;
            }
        }
        return max;
    }

    // Assignment operator
    Matrix<T>& operator=(const Matrix<T>& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Function to multiply the matrix by a vector
    Vector<T> operator*(const Vector<T>& vec) const {
        if (cols() != vec.size()) {
            std::cout << "Incompatible dimensions for matrix-vector multiplication!" << std::endl;
            return Vector<T>();
        }

        Vector<T> result(rows());

        for (std::size_t i = 0; i < rows(); ++i) {
            for (std::size_t j = 0; j < cols(); ++j) {
                result[i] += data[i][j] * vec[j];
            }
        }

        return result;
    }


    void print() const {
        for (const auto& vec : data) {
            vec.print();
        }
    }

    void resize(std::size_t newRowSize, std::size_t newColSize) {
        data.resize(newRowSize, Vector<T>(newColSize));
        matrixSize.first = newRowSize;
        matrixSize.second = newColSize;
    }



};

