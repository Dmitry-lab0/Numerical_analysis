#pragma once
#include <vector>
#include <cmath>
#include <numeric>
#include <random>

template<class T>
class Vector {
private:
    std::vector<T> data;
    std::size_t vectorSize;
public:
    Vector() {}
    Vector<T>(size_t size): data(size) {}
    Vector(const std::vector<T>& vec) : data(vec) {}
    Vector(std::initializer_list<T> init) : data(init) {}
    
    std::vector<T>& getData() {
        return data;
    }

    std::vector<T> getData() const {
        return data;
    }

    // Function to get the size of the vector
    std::size_t size() const {
        return data.size();
    }

    // Function to get the element at a specific index
    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    // Function to perform scalar multiplication with the vector
    Vector<T> operator*(const T num) const {
        Vector<T> result(data.size());
        for (std::size_t i = 0; i < data.size(); i++) {
            result[i] = data[i] * num;
        }
        return result;
    }

    // Function to perform scalar multiplication with the vector
   void zeros(){
        for (std::size_t i = 0; i < data.size(); i++) {
            data[i] =  0;
        }
        return;
    }

    Vector<T> operator-(const Vector<T>& other) const {
        Vector<T> result(*this);
        if (result.size() != other.size()) {
            std::cout << "Vectors must be of equal size for subtraction!" << std::endl;
            return result;
        }
        for (int i = 0; i < result.size(); i++) {
            result[i] -= other[i];
        }
        return result;
    }

    T norm() const {
    T sum = 0;
    for (const T& element : data) {
        sum += element * element;
    }
    return std::sqrt(sum);
    }

    // Function to calculate the || * ||1 norm of the vector
    T norm1() const {
        return std::accumulate(data.begin(), data.end(), T{},
            [](T a, T b) { return a + std::abs(b); });
    }

    // Function to calculate the || * ||∞ norm of the vector
    T normInf() const {
        auto maxElement = std::max_element(data.begin(), data.end(), [](T a, T b) { return std::abs(a) < std::abs(b); });
        return std::abs(*maxElement);
    }

    // Assignment operator
    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    void push_back(const T& value) {
        data.push_back(value);
    }

    void print() const {
        for (const auto& elem : data) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    void resize(std::size_t newSize) {
        data.resize(newSize);
    }

    // Function to add random perturbation to vector elements
    Vector<T> addPerturbation(const T perturbationAmount) {
        Vector<T> noisy_vector(*this);
        std::default_random_engine generator(time(0));
        std::uniform_real_distribution<T> distribution(-perturbationAmount, perturbationAmount);

        for (std::size_t i = 0; i < noisy_vector.size(); i++) {
            noisy_vector[i] += distribution(generator);
        }
        return noisy_vector;
    }



};



//template<class T>
//T norm(std::vector<T>& vec) {
//    T sum = 0;
//    for (const T& element : vec) {
//        sum += element * element;
//    }
//    return std::sqrt(sum);
//}
//
//// Function to perform scalar multiplication with the vector
//template<class T>
//std::vector<T> multNum(const std::vector<T>& vector, const T num) {
//    std::vector<T> result(vector.size(), 0);
//    for (int i = 0; i < vector.size(); i++) {
//        result[i] = vector[i] * num;
//    }
//    return result;
//}
//
//template<class T>
//std::vector<T> diffVectors(const std::vector<T>& vector_1, const std::vector<T>& vector_2) {
//    std::vector<T> result(vector_1.size(), 0);
//    if (vector_1.size() != vector_2.size()) {
//        std::cout << "Vectors must be of equal size for subtraction!" << std::endl;
//        return result;
//    }
//
//    for (int i = 0; i < vector_1.size(); i++) {
//        result[i] = vector_1[i] - vector_2[i];
//    }
//
//    return result;
//}
//
//template<typename T>
//T Norm1(std::vector<T>& vector)
//{
//    return std::accumulate(vector.begin(), vector.end(), T{},
//        [](T a, T b) { return a + std::abs(b); });
//}
//
//template<typename T>
//T Norm1(std::vector<std::vector<T>>& matrix)
//{
//    T max{};
//    for (auto it = matrix[0].begin(); it != matrix[0].end(); ++it)
//    {
//        T res = std::accumulate(matrix.begin(), matrix.end(), T{},
//            [i = it - matrix[0].begin()](T a, std::vector<T>& b) { return a + std::abs(b[i]); });
//        if (max < res)
//        {
//            max = res;
//        }
//    }
//    return max;
//}
//
//template<typename T>
//T NormInf(std::vector<T>& vector)
//{
//    auto maxElement = std::max_element(vector.begin(), vector.end(), [](T a, T b) { return std::abs(a) < std::abs(b); });
//    return std::abs(*maxElement);
//}
//
//template<typename T>
//T NormInf(std::vector<std::vector<T>>& matrix)
//{
//    auto maxRow = std::max_element(matrix.begin(), matrix.end(), [](const auto& a, const auto& b) {
//        return std::accumulate(a.begin(), a.end(), T{},
//        [](T a, T b) { return std::abs(a) + std::abs(b); }) < std::accumulate(b.begin(), b.end(), T{}, [](T a, T b) { return std::abs(a) + std::abs(b); });
//        });
//
//    return std::accumulate(maxRow->begin(), maxRow->end(), T{}, [](T a, T b) { return std::abs(a) + std::abs(b); });
//}
//
//template<typename T>
//std::vector<std::vector<T>> mult(const std::vector<std::vector<T>>& matr1, const std::vector<std::vector<T>>& matr2)
//{
//    std::vector<std::vector<T>> result;
//
//    if (matr1[0].size() != matr2.size()) {
//        std::cout << "Incompatible matrix dimensions for multiplication!" << std::endl;
//        return result;
//    }
//
//    std::size_t rows = matr1.size();
//    std::size_t cols = matr2[0].size();
//    std::size_t common_dim = matr2.size();
//
//
//    result.resize(rows, std::vector<T>(cols, 0));
//
//    for (std::size_t i = 0; i < rows; ++i) {
//        for (std::size_t j = 0; j < cols; ++j) {
//            for (std::size_t k = 0; k < common_dim; ++k) {
//                result[i][j] += matr1[i][k] * matr2[k][j];
//            }
//        }
//    }
//}