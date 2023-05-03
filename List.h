#pragma once
template <typename T>
class List {
public:
     List(int s = 0);
     List(const List<T>& other);
     void push_back(T val);
     void pop_back();
     int size();
     T& operator[](int i);
     void erase(int index);
     void set(int i, T val);
     ~List();

private:
     int counter;
     int size0;
public:
     T* arr;
};

template <typename T>
List<T>::List(int s) {
     size0 = s;
     arr = new T[size0];
     counter = 0;
}

template <typename T>
List<T>::List(const List<T>& other) {
     size0 = other.size0;
     counter = other.counter;
     arr = new T[size0];
     for (int i = 0; i < size0; i++) {
          arr[i] = other.arr[i];
     }
}

template <typename T>
T& List<T>::operator[](int i) {
     if (i < size0) {
          return arr[i];
     }
     else {
          cout << "Out of index" << endl;
          throw out_of_range("List index out of range");
     }
}

template <typename T>
void List<T>::set(int i, T val) {
     if (i < size0) {
          arr[i] = val;
     }
     else {
          cout << "Out of index" << endl;
     }
}

template <typename T>
int List<T>::size() {
     return size0;
}

template <typename T>
void List<T>::push_back(T val) {
     if (counter < size0) {
          arr[counter] = val;
          counter++;
     }
     else {
          List<T> copy(size0 + 1);
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
void List<T>::pop_back() {
     if (counter > 0) {
          counter--;
          List<T> copy(size0 - 1);
          for (int i = 0; i < counter; i++) {
               copy.push_back(arr[i]);
          }
          delete[] arr;
          arr = new T[size0 - 1];
          for (int i = 0; i < size0 - 1; i++) {
               arr[i] = copy[i];
          }
          size0--;
     }
     else {
          std::cout << "List is empty, cannot delete last index." << std::endl;
     }
}

template <typename T>
void List<T>::erase(int index) {
     if (index >= 0 && index < size0) {
          for (int i = index; i < size0 - 1; i++) {
               arr[i] = arr[i + 1];
          }
          size0--;
          counter--;
          T* newArr = new T[size0];
          for (int i = 0; i < size0; i++) {
               newArr[i] = arr[i];
          }
          delete[] arr;
          arr = newArr;
     }
     else {
          std::cout << "Invalid index" << std::endl;
     }
}


template <typename T>
List<T>::~List() {
     //delete[] arr;
}
