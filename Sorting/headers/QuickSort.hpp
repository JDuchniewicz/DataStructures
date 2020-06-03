#pragma once

// this is not very intuitive algorithm with this code..
// basically take highest as pivot, then compare all elements to it and swap them if they are <smaller|greater> than it is, then swap pivot with the last moved element -> the rest is already greater than it is
#include <Utils.hpp>

// end is a pivot which is placed in its proper place
// all elements <smaller|greater> than pivot are placed before it (to the left), and the rest is placed to the right
template<typename T>
int partition(T* input, int start, int end)
{
    int pivot = input[end];
    int i = start - 1; // smaller element

    for (int j = start; j <= end; ++j)
    {
        if (input[j] < pivot) // or greater in the other impl
            swap(input, ++i, j);
    }
    swap(input, i + 1, end);
    return i + 1;
}

template<typename T>
void recursiveQuickSort(T* input, int start, int end)
{
    if (start >= end)
        return;
    
    int partIdx = partition(input, start, end);

    // sort left and right half recursively, leave partitionIdx in place
    recursiveQuickSort(input, start, partIdx - 1);
    recursiveQuickSort(input, partIdx + 1, end);
}

template<typename T>
void iterativeQuickSort(T* input, int start, int end)
{
    int stack[end - start + 1];
    int top = -1, partIdx = 0;
    stack[++top] = start;
    stack[++top] = end;

    // stack contains all indices of subarrays' starts and ends
    while (top >= 0)
    {
        end = stack[top--];
        start = stack[top--];
        
        partIdx = partition(input, start, end);

        // if there are elements to the left of partIdx, it can be further subdivided, so add another iteration on a smaller partition
        if (partIdx - 1 > start)
        {
            stack[++top] = start;
            stack[++top] = partIdx - 1;
        }

        if (partIdx + 1 < end)
        {
            stack[++top] = partIdx + 1;
            stack[++top] = end;
        }
    }
}