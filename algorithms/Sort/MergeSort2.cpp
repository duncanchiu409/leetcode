#include <iostream>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"

using namespace std;

void mergeArr(std::vector<int> &arr, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> L(n1), R(n2);
    int index_1 = 0;
    for (int i = left; i < middle + 1; ++i)
    {
        L[index_1] = arr[i];
        ++index_1;
    }
    int index_2 = 0;
    for (int i = middle + 1; i < right + 1; ++i)
    {
        R[index_2] = arr[i];
        ++index_2;
    }

    int i = 0, j = 0, index = left;
    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            arr[index] = L[i];
            ++i;
            ++index;
        }
        else
        {
            arr[index] = R[j];
            ++j;
            ++index;
        }
    }

    while (i < n1)
    {
        arr[index] = L[i];
        ++i;
        ++index;
    }

    while (j < n2)
    {
        arr[index] = R[j];
        ++j;
        ++index;
    }
}

void mergeSortRecursive(std::vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;
    int middle = left + (right - left) / 2;
    mergeSortRecursive(arr, left, middle);
    mergeSortRecursive(arr, middle + 1, right);
    mergeArr(arr, left, middle, right);
}

void printVector(std::vector<int> arr)
{
    for (int i : arr)
    {
        cout << i << " ";
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
    mergeSortRecursive(arr, 0, n - 1);
    printVector(arr);
}