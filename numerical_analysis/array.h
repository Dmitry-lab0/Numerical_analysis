#pragma once
#include <iostream>

template <class T>
class Array {
private:
    T* arr=nullptr; // Pointer to the array
    int size=0; // Size of the array

public:
    // Constructors
    Array() {}
    Array(int s) {
        size = s;
        arr = new T[size];
    }

    // Destructor
    ~Array() {
        delete[] arr;
    }


    void fill(const T element) {
        for (int i = 0; i < size; i++) {
            arr[i] = element;
        }
    }
    // Function to initialize all elements with zeros
    void zeros() {
        fill(T());
    }

    void setElement(int index, T value) {
        if (index >= 0 && index < size) {
            arr[index] = value;
        }
        else {
            std::cout << "Invalid index!" << std::endl;
        }
    }

    T getElement(int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        else {
            std::cout << "Invalid index!" << std::endl;
            return T(); // or any other default value
        }
    }

    int getSize() {
        return size;
    }

    // WARNING! operations change the vector
    // this approach more efficient

    void plusArray(const Array<T>& other) {
        if (size != other.size) {
            std::cout << "Arrays must be of equal size for addition!" << std::endl;
            return;
        }

        //Array<T> result(size);

        for (int i = 0; i < size; i++) {
            setElement(i, arr[i] + other.arr[i]);
        }

        return;
    }

    // Function to perform element-wise subtraction with another array
    void minusArray(const Array<T>& other) {
        if (size != other.size) {
            std::cout << "Arrays must be of equal size for subtraction!" << std::endl;
            return;
        }

        //Array<T> result(size);

        for (int i = 0; i < size; i++) {
            setElement(i, arr[i] - other.arr[i]);
        }

        return;
    }
    
    // Function to perform scalar multiplication with the array
    void multNum(const T& num) const {
        //Array<T> result(size);

        for (int i = 0; i < size; i++) {
            this->arr[i] = arr[i] * num;
        }

        return;
    }

    // Function to calculate the dot product with another array
    void dot(const Array<T>& other) const {
        if (size != other.size) {
            std::cout << "Arrays must be of equal size for dot product!" << std::endl;
            return; // or any other default value
        }

        //T result = T();

        for (int i = 0; i < size; i++) {
            arr[i] *=other.arr[i];
        }

        return;
    }

    // element access operator
    T& operator()(int index) {
        return arr[index];
    }

    void swap(Array<T>& second) {
        std::swap(*this, second);
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};
