#pragma once
#include <vector>
#include <iostream>
#include <functional>
#include "vector.h"
#include "matrix.h"
#include "utils.h"

template <class T>
class LinearSystem{
protected:
    Matrix<T> A; // coefficient matrix
    Vector<T> b; // right side vector
    Vector<T> x; // unknown variable
    T eps = 0.1e-10; // threshold for considering values as zero.
    int normType = 2;// 0 - || * ||∞ norm, 1 - || * ||1 norm, 2 - Euclidean norm
    bool isSolved = false;
public:
    // Constructor
    LinearSystem(Matrix<T>& matrix, Vector<T>& vectorB, bool copyMatrix, bool isSolved = false) {
        if (copyMatrix) {
            A = matrix;
            b = vectorB;
        }
        else {
            A = std::move(matrix);
            b = std::move(vectorB);
        }
    }

    Matrix<T>& getMatrix() {
        return A;
    }

    Vector<T>& getX() {
        if (isSolved) {
            return x;
        }
        else {
            throw std::runtime_error("There is no solution, solve the system first!");
        }
    }

    void setEps(T new_eps) {
        eps = new_eps;
    }

    void setNorm(int new_norm) {
        if (new_norm >= 0 && new_norm <= 2) {
            normType = new_norm;
        }
        else {
            // Print an error message or throw an exception
            std::cout << "Invalid norm value. Valid values are 0, 1, or 2." << std::endl;
        }
    }

    T norm(Vector<T>& vector) {
        if (normType == 0) {
            return vector.normInf();
        }
        else if(normType == 1) {
            return vector.norm1();
        }
        else {
            return vector.norm();
        }
    }


    T getResidualNorm() {
        if (isSolved) {
            Vector<T> residual = A * x - b;
            return norm(residual);
        }
    }


};