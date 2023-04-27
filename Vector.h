#pragma once
#include <iostream>

template <typename T>
class Vector {
public:
    Vector(int s = 0);
    void push_back(T val);
    int size();
    T operator[](int i);
    ~Vector();

private:
    int counter;
    int size0;
    T* arr;
};

template <typename T>
Vector<T>::Vector(int s) {
    size0 = s;
    arr = new T[size0];
    counter = 0;
}

template <typename T>
T Vector<T>::operator[](int i) {
    if (i < size0) {
        return arr[i];
    }
    else {
        std::cout << "Out of index" << std::endl;
        return T();
    }
}

template <typename T>
int Vector<T>::size() {
    return size0;
}

template <typename T>
void Vector<T>::push_back(T val) {
    if (counter < size0) {
        arr[counter] = val;
        counter++;
    }
    else {
        Vector<T> copy(size0 + 1);
        for (int i = 0; i < size0; i++) {
            copy.push_back(arr[i]);
        }
        copy.push_back(val);
        delete[] arr;
        arr = new T[size0 + 1];
        for (int i = 0; i < size0 + 1; i++) {
            arr[i] = copy[i];
        }
        size0++;
        counter++;
    }
}

template <typename T>
Vector<T>::~Vector() {
    //delete[] arr;
}
