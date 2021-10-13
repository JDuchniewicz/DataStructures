#pragma once

#include "Utils.hpp" // according to C++ standard angled includes are only for external libraries
#include <map>

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

template<typename T>
void bucketSortMap(T* input, int size)
{
    std::map<T, int> occurences;
    for (int i = 0; i < size; ++i)
    {
        if (occurences.count(input[i]) > 0)
            ++occurences.at(input[i]);
        else
            occurences.emplace(input[i], 1);
    }

    int sortedIdx = 0;
    for (auto& [v, times] : occurences)
    {
        while (times--)
            input[sortedIdx++] = v;
    }
}
