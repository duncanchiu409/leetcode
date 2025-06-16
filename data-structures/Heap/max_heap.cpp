#include <algorithm>
#include <climits>
#include <iostream>

template <typename T> class MaxHeap {
private:
  T *arr;
  int capacity;
  int heap_size;

public:
  MaxHeap(int);
  int getParent(int);
  int getLeftChild(int);
  int getRightChild(int);

  void increaseKey(int, T);
  void heapify(int);
  T extractMax();

  void insertKey(T);
  void deleteKey(T);
};

template <typename T> MaxHeap<T>::MaxHeap(int capacity) {
  this->arr = new T[capacity];
  this->capacity = capacity;
  this->heap_size = 0;
}

template <typename T> int MaxHeap<T>::getParent(int index) {
  return (index - 1) / 2;
}

template <typename T> int MaxHeap<T>::getLeftChild(int index) {
  return 2 * index + 1;
}

template <typename T> int MaxHeap<T>::getRightChild(int index) {
  return 2 * index + 2;
}

template <typename T> void MaxHeap<T>::increaseKey(int index, T value) {
  this->arr[index] = value;
  int parent = this->getParent(index);
  while (index != 0 && this->arr[index] < this->arr[parent]) {
    std::swap(this->arr[index], this->arr[parent]);
    index = parent;
  }
}

template <typename T> T MaxHeap<T>::extractMax() {
  if (this->heap_size == 0) {
    std::cout << "Invalid Operation ..." << std::endl;
  }
  if (this->heap_size == 1) {
    --this->heap_size;
    return this->arr[0];
  } else {
    T root = this->arr[0];
    --this->heap_size;
    this->arr[0] = this->arr[this->heap_size];
    this->heapify(0);
    return root;
  }
}

template <typename T> void MaxHeap<T>::heapify(int index) {
  int left = this->getLeftChild(index);
  int right = this->getRightChild(index);
  int biggest = index;
  if (left <= this->heap_size && this->arr[biggest] < this->arr[left]) {
    biggest = left;
  }
  if (right <= this->heap_size && this->arr[biggest] < this->arr[right]) {
    biggest = right;
  }
  if (biggest != index) {
    std::swap(this->arr[index], this->arr[biggest]);
    this->heapify(biggest);
  }
}

template <typename T> void MaxHeap<T>::insertKey(T key) {
  if (this->heap_size < this->capacity) {
    int index = this->heap_size;
    this->arr[index] = key;
    int parent = this->getParent(index);
    ++this->heap_size;
    while (index != 0 && this->arr[parent] < this->arr[index]) {
      std::swap(this->arr[index], this->arr[parent]);
      index = parent;
    }
  }
}

template <typename T> void MaxHeap<T>::deleteKey(int index) {
  this->deleteKey(int index, INT_MAX);
  this->extractMax();
}
