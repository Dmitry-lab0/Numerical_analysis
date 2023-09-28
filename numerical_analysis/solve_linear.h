#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include "linear_system.h"
#include "vector.h"
#include "matrix.h"

template <class T>
class Gauss: public LinearSystem<T> {
private:
    Matrix<T> upperTriangular;
    Vector<T> changed_b;
    bool forward_pass = false;

    int findMaxColElement(int i, Matrix<T>& matrix) {
        int IndexMaxRow = i;
        for (int j = i + 1; j < matrix.cols(); ++j) {
            if (abs(matrix[j][i]) > abs(matrix[IndexMaxRow][i])) { IndexMaxRow = j; }
        }
        return IndexMaxRow;
    }

    void forward() {
        if (!forward_pass) {
            upperTriangular = this->A;
            changed_b = this->b;
            size_t size = upperTriangular.rows();
            T coef = T();
            int IndexMaxRow = 0;
            for (int i = 0; i < size; ++i) {
                IndexMaxRow = findMaxColElement(i, upperTriangular);
                std::swap(upperTriangular[i], upperTriangular[IndexMaxRow]);
                std::swap(changed_b[i], changed_b[IndexMaxRow]);

                for (int j = i + 1; j < size; ++j) {
                    coef = upperTriangular[j][i] / upperTriangular[i][i];
                    upperTriangular[j][i] = 0;
                    changed_b[j] -= changed_b[i] * coef;
                    for (int k = i + 1; k < size; ++k) {
                        upperTriangular[j][k] -= upperTriangular[i][k] * coef;
                    }
                }
            }
            forward_pass = true;
        }
    }

    void backward() {
        size_t size = this->upperTriangular.rows();
        Vector<T> solution(size);
        for (int i = size - 1; i >= 0; --i) {
            solution[i] = this->changed_b[i];
            for (int j = size - 1; j > i; --j) {
                solution[i] -= this->upperTriangular[i][j] * solution[j];
            }
            solution[i] /= this->upperTriangular[i][i];
        }
        this->x = solution;
    }




public:
    // Constructor
    Gauss(Matrix<T>& matrix, Vector<T>& vectorB, bool copyMatrix = true, bool forward_pass = false, bool isSolved = false) : LinearSystem<T>(matrix, vectorB, copyMatrix, isSolved) {
    }

    bool isDeterminantNonZero() {
        if (!forward_pass) {
            forward();
        }

        for (int i = 0; i < upperTriangular.size(); i++) {
            if (std::abs(upperTriangular[i][i]) < this->eps) {
                return false;
            }
        }

        return true;
    }

    Matrix<T>& getMatrix() {
            return this->A;
    }
    

    Vector<T> solveSystem() {
        if (!forward_pass) {
            this->forward();
        }
        if (isDeterminantNonZero()) {
            backward();
            this->isSolved = true;
            return this->x;
        }
        else {
            throw std::runtime_error("Determinant is zero, system has no unique solution.");
        }

    }
    
    void setB(Vector<T>& vectorB) {
        this->b = vectorB;
        forward_pass = false;
    }

};

template <class T>
class QR : public LinearSystem<T> {
private:
    Matrix<T> Q;
    Matrix<T> R;
    Vector<T> rotated_b;
    bool rotated = false;

    void rotate() {
        if (!rotated) {
            size_t size = this->A.rows();
            R = this->A;
            rotated_b = this->b;
            T aii = 0;
            T aii_square = 0;
            T aji = 0;
            T aji_square = 0;
            T norm = 0;
            T coef_1 = 0;
            T coef_2 = 0;
            T aik = 0;
            T ajk = 0;
            T bi = 0;
            T bj = 0;
            T qki = 0;
            T qkj = 0;
            for (int i = 0; i < size - 1; ++i) {
                for (int j = i + 1; j < size; ++j) {
                    aji = R[j][i];
                    if (abs(aji) > this->eps) {
                        aii = R[i][i];
                        bi = rotated_b[i];
                        norm = std::sqrt(aji * aji + aii * aii);
                        coef_1 = aii / norm;
                        coef_2 = aji / norm;
                        bj = rotated_b[j];
                        rotated_b[i] = bi * coef_1 + bj * coef_2;
                        rotated_b[j] = bi * (-coef_2) + bj * coef_1;
                        for (int k = 0; k < size; ++k) {
                            aik = R[i][k];
                            ajk = R[j][k];
                            R[i][k] = aik * coef_1 + ajk * coef_2;
                            if (k == i) {
                                R[j][k] = 0;
                            }
                            else {
                                R[j][k] = aik * (-coef_2) + ajk * coef_1;
                            }
                            qki = Q[k][i];
                            qkj = Q[k][j];
                            Q[k][i] = qki * coef_1 + qkj * coef_2;
                            Q[k][j] = qki * (-coef_2) + qkj * coef_1;
                        }
                    }
                    else {
                        R[j][i] = 0;
                    }
                }
                //std::cout << "Modified Matrix<T> A:" << std::endl;
                //for (const auto& row : R) {
                //    for (const auto& element : row) {
                //        std::cout << element << " ";
                //    }
                //    std::cout << std::endl;
                //}
            }
        }
        rotated = true;
    }

    void backward() {
        Gauss<T> gaussSolver(R, rotated_b, false, true);
        gaussSolver.solveSystem();
        this->x = gaussSolver.getX();
        this->R = std::move(gaussSolver.getMatrix());
    }

public:
    // Constructor
    QR(Matrix<T>& matrix, Vector<T>& vectorB, bool copyMatrix = true, bool isSolved = false) : LinearSystem<T>(matrix, vectorB, copyMatrix, isSolved) {
        Q.resize(this->A.rows(), this->A.cols());
        for (int i = 0; i < this->A.rows(); i++) {
            for (int j = 0; j < this->A.cols(); j++)
            {
                if (i == j) { Q[i][j] = 1.0; }
                else { Q[i][j] = 0.0; }
            }
        }
    }

    bool isDeterminantNonZero() {
        if (!rotated) {
            rotate();
        }

        for (int i = 0; i < R.size(); i++) {
            if (std::abs(R[i][i]) < this->eps) {
                return false;
            }
        }

        return true;
    }

    Matrix<T>& getR(){
        if (rotated) {
            return R;
        }
        else {
            rotate();
            return R;

        }
        
    }


    Matrix<T>& getQ() {
        if (rotated) {
            return Q;
        }
        else {
            rotate();
            return Q;
        }
    }
    
    Vector<T>& solveSystem() {
        if (!rotated) {
            this->rotate();
        }
        if (isDeterminantNonZero()) {
            backward();
            this->isSolved = true;
            return this->x;
        }
        else {
            throw std::runtime_error("Determinant is zero, system has no unique solution.");
        }
    }

    void setB(Vector<T>& vectorB) {
        this->b = vectorB;
        rotated = false;
    }

};


