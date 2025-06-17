#include <iostream>
#include <vector>
#include <algorithm>

void heapify(std::vector<int> nums, int n, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int biggest = index;

    if (left < n && nums[biggest] < nums[left])
    {
        biggest = left;
    }

    if (right < n && nums[biggest] < nums[right])
    {
        biggest = right;
    }

    if (index != biggest)
    {
        std::swap(nums[index], nums[biggest]);
        heapify(nums, n, biggest);
    }
}

void HeapSort(std::vector<int> nums)
{
    int n = nums.size();
}