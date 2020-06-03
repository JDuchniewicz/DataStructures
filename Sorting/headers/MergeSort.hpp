#pragma once
#include <algorithm>

template<typename T>
void merge(T* input, int left, int middle, int right)
{
    int leftSize = middle - left + 1; // +1 because we include middle element
    int rightSize = right - middle;

    T leftA[leftSize], rightA[rightSize];

    // copy data to temporary arrays
    for (int i = 0; i < leftSize; ++i)
        leftA[i] = input[left + i];
    for (int i = 0; i < rightSize; ++i)
        rightA[i] = input[middle + 1 + i];

    int l = 0, r = 0, s = left; // indices for left, right and sum (merged) - start accessing from leftmost index
    while (l < leftSize && r < rightSize)
    {
        if (leftA[l] <= rightA[r]) // comparator?
        {
            input[s] = leftA[l];
            ++l;
        }
        else
        {
            input[s] = rightA[r];
            ++r;
        }
        ++s;
    }

    // add rest of left
    while (l < leftSize)
        input[s++] = leftA[l++];

    // add rest of right
    while (r < rightSize)
        input[s++] = rightA[r++];
}

template<typename T>
void recursiveMergeSort(T* input, int left, int right)
{
    if (left >= right) // array size is less than one
        return;

    int middle = left + (right - left)/2; // trick to prevent overflow

    // sort left and right half
    recursiveMergeSort(input, left, middle);
    recursiveMergeSort(input, middle + 1, right);
    
    merge(input, left, middle, right);
}

template<typename T>
void iterativeMergeSort(T* input, int size)
{
    int mergeSize = 0, leftStart = 0;
    // iteratively merge subarrays, start with arrays of size 1, then 2, then 4 etc - a bottom-up approach
    for (mergeSize = 1; mergeSize < size; mergeSize <<= 1)
    {
        // pick starting point for subarrays of current size
        for (leftStart = 0; leftStart < size - 1; leftStart += (mergeSize << 1))
        {
            // find end point of left subarray
            int mid = std::min(leftStart + mergeSize - 1, size - 1); // min's are for ensuring boundaries for not mutliples of 2
            int rightEnd = std::min(leftStart + (mergeSize << 1) - 1, size - 1);
            // merge subarrays 
            merge(input, leftStart, mid, rightEnd);
        }
    }
}