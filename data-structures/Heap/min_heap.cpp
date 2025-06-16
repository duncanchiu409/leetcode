#include <algorithm>
#include <climits>
#include <utility>

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

class MinHeap {
public:
  int *heap_arr;
  int capacity;
  int heap_size;

  MinHeap(int);
  int getParent(int);
  int getLeftChild(int);
  int getRightChild(int);

  int extractMin();
  void decreaseKey(int, int);
  void insertKey(int);
  void deleteKey(int);
  void heapify(int);
  int getMin();
};

MinHeap::MinHeap(int capacity) {
  this->heap_arr = new int(capacity);
  this->capacity = capacity;
  this->heap_size = 0;
}

int MinHeap::getParent(int index) { return (index - 1) / 2; }

int MinHeap::getLeftChild(int index) { return 2 * index + 1; }

int MinHeap::getRightChild(int index) { return 2 * index + 2; }

int MinHeap::extractMin() {
  if (this->heap_size == 0) {
    return INT_MAX;
  }
  if (this->heap_size == 1) {
    --this->heap_size;
    return heap_arr[0];
  }

  int root = this->heap_arr[0];
  this->heap_arr[0] = this->heap_arr[this->heap_size - 1];
  --this->heap_size;
  this->heapify(0);
  return root;
}

void MinHeap::decreaseKey(int index, int value) {
  this->heap_arr[index] = value;
  while (index != 0 &&
         this->heap_arr[this->getParent(index)] > this->heap_arr[index]) {
    swap(this->heap_arr[this->getParent(index)], this->heap_arr[index]);
    index = this->getParent(index);
  }
}

void MinHeap::insertKey(int key) {
  if (this->heap_size < this->capacity) {
    this->heap_arr[this->heap_size] = key;
    ++this->heap_size;

    int index = this->heap_size - 1;
    while (index != 0 &&
           this->heap_arr[this->getParent(index)] > this->heap_arr[index]) {
      swap(this->heap_arr[index], this->heap_arr[getParent(index)]);
      index = this->getParent(index);
    }
  }
}

void MinHeap::deleteKey(int key) {
  this->decreaseKey(key, INT_MIN);
  this->extractMin();
}

void MinHeap::heapify(int index) {
  int left = this->getLeftChild(index);
  int right = this->getRightChild(index);
  int smallest = index;
  if (left < this->heap_size &&
      this->heap_arr[left] < this->heap_arr[smallest]) {
    smallest = left;
  }
  if (right < this->heap_size &&
      this->heap_arr[right] < this->heap_arr[smallest]) {
    smallest = right;
  }
  if (smallest != index) {
    swap(this->heap_arr[index], this->heap_arr[smallest]);
    this->heapify(smallest);
  }
}

int MinHeap::getMin() { return this->heap_arr[0]; }

TEST_CASE("TEST MinHeap 01") {
  MinHeap h(11);
  h.insertKey(3);
  h.insertKey(2);
  h.deleteKey(1);
  h.insertKey(15);
  h.insertKey(5);
  h.insertKey(4);
  h.insertKey(45);
  cout << h.extractMin() << " ";
  cout << h.getMin() << " ";
  h.decreaseKey(2, 1);
  cout << h.getMin();
}
