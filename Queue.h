#pragma once
template <typename T>
class Queue {
public:
     void enqueue(T val);
     void dequeue();
     T front();
     bool empty();
     int size();

private:
     List<T> data;
};

template <typename T>
void Queue<T>::enqueue(T val) {
     data.push_back(val);
}

template <typename T>
void Queue<T>::dequeue() {
     if (!empty()) {
          data.erase(0);
     }
     else {
          std::cout << "Queue is empty, cannot dequeue." << std::endl;
     }
}

template <typename T>
T Queue<T>::front() {
     if (!empty()) {
          return data[0];
     }
     else {
          std::cout << "Queue is empty, cannot access front element." << std::endl;
          return T();
     }
}

template <typename T>
bool Queue<T>::empty() {
     return data.size() == 0;
}

template <typename T>
int Queue<T>::size() {
     return data.size();
}


template<typename T>
void custom_swap(T& a, T& b) {
     T temp = a;
     a = b;
     b = temp;
}



//Priorty Queue
template<typename T>
class CustomPriorityQueue {
public:
     void push(T val)
     {
          data.push_back(val);
          int i = data.size() - 1;
          while (i > 0 && data[i] < data[(i - 1) / 2])
          {
               custom_swap(data[i], data[(i - 1) / 2]);
               i = (i - 1) / 2;
          }
     }
     T top() 
     {
          return data[0];
     }
     void pop()
     {
          int n = data.size();
          if (n == 0) return;

          data.set(0, data[n - 1]);
          data.pop_back();
          n--;

          int i = 0;
          while (true) {
               int left = 2 * i + 1;
               int right = 2 * i + 2;
               int smallest = i;

               if (left < n && data[left] < data[smallest]) {
                    smallest = left;
               }
               if (right < n && data[right] < data[smallest]) {
                    smallest = right;
               }

               if (smallest == i) {
                    break;
               }

               custom_swap(data[i], data[smallest]);
               i = smallest;
          }
     }
     bool empty() 
     {
          return data.size() == 0;
     }

private:
     List<T> data;
};
