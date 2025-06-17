#include <iostream>

class MinHeap
{
public:
  int *arr;
  int capacity;
  int size;

  MinHeap(int);
  ~MinHeap();

  // Helper Function
  void decreaseKey(int, int);
  void heapify(int);

  // Main Function
  int getMin();
  int extractMin();
  void insertKey(int);
  void deleteKey(int);
};

MinHeap::MinHeap(int capacity)
{
  this->arr = new int[capacity];
  this->capacity = capacity;
  this->size = 0;
}

MinHeap::~MinHeap() { delete[] this->arr; }

void MinHeap::decreaseKey(int index, int value)
{
  this->arr[index] = value;
  int parent = (index - 1) / 2;
  while (index != 0 && this->arr[parent] > this->arr[index])
  {
    std::swap(this->arr[index], this->arr[parent]);
    index = parent;
    parent = (index - 1) / 2;
  }
}

void MinHeap::heapify(int index)
{
  int leftChild = index * 2 + 1;
  int rightChild = index * 2 + 2;
  int smallest = index;

  if (leftChild < this->size && this->arr[leftChild] < this->arr[smallest])
  {
    smallest = leftChild;
  }

  if (rightChild < this->size && this->arr[rightChild] < this->arr[smallest])
  {
    smallest = rightChild;
  }

  if (smallest != index)
  {
    std::swap(this->arr[smallest], this->arr[index]);
    this->heapify(smallest);
  }
}

int MinHeap::getMin()
{
  if (this->size == 0)
  {
    return INT_MAX;
  }
  else
  {
    return this->arr[0];
  }
}

int MinHeap::extractMin()
{
  if (this->size == 0)
  {
    return INT_MAX;
  }
  else if (this->size == 1)
  {
    --this->size;
    return this->arr[0];
  }
  else
  {
    int root = this->arr[0];
    --this->size;
    std::swap(this->arr[this->size], this->arr[0]);
    this->heapify(0);
    return root;
  }
}

void MinHeap::insertKey(int key)
{
  if (this->size < this->capacity)
  {
    this->arr[this->size] = key;
    int index = ++this->size;
    int parent = (index - 1) / 2;
    while (index != 0 && this->arr[index] < this->arr[parent])
    {
      std::swap(this->arr[index], this->arr[parent]);
      index = parent;
      parent = (index - 1) / 2;
    }
  }
}

void MinHeap::deleteKey(int index)
{
  this->decreaseKey(index, INT_MIN);
  this->extractMin();
}