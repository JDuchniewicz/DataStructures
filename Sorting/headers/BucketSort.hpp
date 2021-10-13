#pragma once

#include <Utils.hpp>

template <typename T>
void bucketSort(T* input, int size, T maxValue) // the unoptimal version with O(n) memory
{
    T* occurences = new T[maxValue];
    for (int i = 0; i < size; ++i)
        ++occurences[input[i]];

    int sortedIdx = 0;
    for (int i = 0; i < maxValue; ++i)
        while(occurences[i]-- > 0)
            input[sortedIdx++] = i;


    delete[] occurences;
}
