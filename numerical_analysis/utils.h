#pragma once
#include <iostream>
#include "matrix.h"
#include "solve_linear.h"
#include <fstream>
#include <sstream>
#include <string>

template<class T>
Matrix<T> inverseMatrix(Matrix<T>& matrix) {
    // Check if A is a square matrix
    if (matrix.rows() != matrix.cols()) {
        throw std::runtime_error("Matrix A is not square. Inverse does not exist.");
    }
    // Create a  matrix of the same size as A
    Matrix<T> inverse(matrix);
    Vector<T> identity_column(matrix.rows());
    Vector<T> inverse_column(matrix.rows());
    identity_column.zeros();
    Gauss<T> solver(matrix, identity_column);

    // Solve the equation A * inverse = Identity for inverse
    for (int j = 0; j < matrix.cols(); ++j) {
        identity_column[j] = 1;
        solver.setB(identity_column);
        inverse_column = solver.solveSystem();
        for (int i = 0; i < matrix.cols(); ++i) {
            inverse[i][j] = inverse_column[i];
        }
        identity_column.zeros();
    }
    return inverse;
}

template<class T>
T getConditionNumber(Matrix<T>& matrix, int normType=0) {
    // 0 - || * || ∞ norm, 1 - || * || 1 norm
    if (normType >= 0 && normType <= 1) {
        Matrix<T> inverse(inverseMatrix(matrix));

        if (normType == 0) {
            return inverse.normInf() * matrix.normInf();
        }
        else {
            return inverse.norm1() * matrix.norm1();
        }
    }
    else {
        throw std::runtime_error("Invalid norm value. Valid values are 0, or 1");
    }
}

template<class T>
T estimateConditionNumber(Matrix<T>& A, Vector<T>& b, int normType = 0) {
    if (normType >= 0 && normType <= 2) {
        Vector<T> noisy_vector = b.addPerturbation(0.1);
        Gauss<T> solver(A, b);
        T max_estimation = -1;
        T estimation;
        for (int i = 0; i < 4; ++i) {
            solver.setB(b);
            Vector<T> solution_for_b = solver.solveSystem();
            solver.setB(noisy_vector);
            Vector<T> solution_for_noisy_vector = solver.solveSystem();
            Vector<T> diff_1 = b - noisy_vector;
            Vector<T> diff_2 = solution_for_b - solution_for_noisy_vector;
            T delta_x;
            T delta_b;
            T norm_b;
            T norm_x;
            if (normType == 2) {
                delta_x = diff_2.norm();
                delta_b = diff_1.norm();
                norm_b = b.norm();
                norm_x = solution_for_b.norm();
            }
            else if (normType == 1) {
                delta_x = diff_2.norm1();
                delta_b = diff_1.norm1();
                norm_b = b.norm1();
                norm_x = solution_for_b.norm1();
            }
            else {
                delta_x = diff_2.normInf();
                delta_b = diff_1.normInf();
                norm_b = b.normInf();
                norm_x = solution_for_b.normInf();
            }
            estimation = (delta_x / norm_x) / (delta_b / norm_b);
            if (max_estimation < estimation) {
                max_estimation = estimation;
            }
        }
        return max_estimation;
    }
    else {
        throw std::runtime_error("Invalid norm value. Valid values are 0, 1 or 2");
    }
    
}

// Function to open file and read matrix
template<class T>
Matrix<T> readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<std::vector<T>> matrixData;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<T> row;
        std::stringstream ss(line);
        T value;
        while (ss >> value) {
            row.push_back(value);
        }
        matrixData.push_back(row);
    }

    return Matrix<T>(matrixData);
}

// Function to open file and read vector
template<class T>
Vector<T> readVectorFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<T> vectorData;
    std::string line;
    while (std::getline(file, line)) {
        T value;
        std::stringstream ss(line);
        while (ss >> value) {
            vectorData.push_back(value);
        }
    }

    return Vector<T>(vectorData);
}


template<class T>
void writeSolutionToFile(const Vector<T>& solution, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    for (const auto& element : solution.getData()) {
        file << element << std::endl;
    }
}