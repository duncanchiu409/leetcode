#include <iostream>

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"

void merge(vector<int> &nums, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L1(n1), R1(n2);

    for (int i = 0; i < n1; ++i)
    {
        L1[i] = nums[left + i];
    }

    for (int i = 0; i < n2; ++i)
    {
        R1[i] = nums[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L1[i] < R1[j])
        {
            nums[k] = L1[i];
            ++i;
        }
        else
        {
            nums[k] = R1[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        nums[k] = L1[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        nums[k] = R1[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int> &nums, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}

void printVector(vector<int> nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        cout << nums[i] << " ";
    }
}

TEST_CASE("MergeSort TESTCASE 01: ")
{
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    cout << "Before MergeSort: ";
    printVector(arr);
    cout << endl;
    cout << "After MergeSort: ";
    mergeSort(arr, 0, n - 1);
    printVector(arr);
}