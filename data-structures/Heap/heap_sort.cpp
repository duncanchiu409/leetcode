#include <iostream>
#include <vector>

void heapify(std::vector<int> nums, int n, int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int biggest = i;
  if (left < n && nums[biggest] < nums[left]) {
    biggest = left;
  }
  if (right < n && nums[biggest] < nums[right]) {
    biggest = right;
  }
  if (i != biggest) {
    std::swap(nums[i], nums[biggest]);
    heapify(nums, n, biggest);
  }
}

void heapSort(std::vector<int> nums) {
  int n = nums.size();

  for (int i = n / 2 - 1; i > -1; --i) {
    heapify(nums, n, i);
  }

  for (int j = n - 1; j > 0; --j) {
    std::swap(nums[0], nums[j]);
    heapify(nums, j, 0);
  }
}
