#pragma once

#include <Utils.hpp>

template<typename T>
void insertionSort(T* input, int size)
{
    for (int i = 1; i < size; ++i)
    {
        int j = i - 1;
        int key = input[i];
        while (j >= 0 && input[j] > key)
        {
            input[j + 1] = input[j];
            --j;
        }
        input[j + 1] = key;
    }
}