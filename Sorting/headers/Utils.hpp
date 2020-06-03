#pragma once

template<typename T>
void swap(T* input, int a, int b)
{
    T tmp = input[a];
    input[a] = input[b];
    input[b] = tmp;
}