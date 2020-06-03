#pragma once
#include <iostream>

// T has to provide comparator
template<typename T>
class Heap
{
public:
    Heap(int size, bool minHeap)
    {
        m_minHeap = minHeap;
        m_capacity = size;
        m_currentSize = 0;
        m_data = new T[m_capacity + 1];
    }

    Heap(T* from, int size, bool minHeap)
    {
        m_minHeap = minHeap;
        m_capacity = size;
        m_data = new T[m_capacity + 1];
        if (size > 0)
            for (int i = 1; i < size + 1; ++i)
                push(from[i]);
    }

    ~Heap()
    {
        delete[] m_data;
    }

    void display() const
    {
        for (int i = 1; i < m_currentSize + 1; ++i)
            std::cout << m_data[i] << " ";
        std::cout << std::endl;
    }

    void push(T element)
    {
        if (m_currentSize == m_capacity)
        {
            std::cout << "Heap is full: " << m_capacity << " cannot add element: " << element << std::endl;
            return;
        }
        ++m_currentSize;
        m_data[m_currentSize] = element;
        heapUp(m_currentSize);
    }

    T pop()
    {
        T extremum = m_data[1]; // always the first index
        m_data[1] = m_data[m_currentSize]; // break the heap property
        m_data[m_currentSize] = T{}; // this will in turn zero out the compared value in the T
        heapDown(1);
        --m_currentSize;
        return extremum;
    }

    bool remove(T element)
    {
        int currentIdx = 1;
        if (m_minHeap && element < m_data[currentIdx]) // no such element
            return false;
        else if (element > m_data[currentIdx])
            return false;

        while (currentIdx != m_currentSize)
        {
            // found it, remove
            if (m_data[currentIdx] == element)
            {
                swap(1, currentIdx);
                pop();
                return true;
            }
            ++currentIdx;
        }
        return false;
    }

    void heapDown(int idx)
    {
        int smallestGreatest = idx;
        int leftChildIdx = 2 * idx;
        int rightChildIdx = 2 * idx + 1;
        if (leftChildIdx < m_currentSize && !compare(smallestGreatest, leftChildIdx))
            smallestGreatest = leftChildIdx;
        if (rightChildIdx < m_currentSize && !compare(smallestGreatest, rightChildIdx))
            smallestGreatest = rightChildIdx;
        if (smallestGreatest != idx)
        {
            swap(idx, smallestGreatest);
            heapDown(smallestGreatest);
        }
    }

    void heapUp(int idx)
    {
        int parentIdx = idx / 2;
        int currentIdx = idx;
        while (currentIdx > 0 && !compare(parentIdx, currentIdx) && parentIdx != 0)
        {
            swap(parentIdx, currentIdx);
            currentIdx = parentIdx;
            parentIdx /= 2;
        }
    }

    bool isEmpty() const
    {
        return m_currentSize == 0;
    }

private:
    bool compare(int parent, int current) const // returns true if heap property is satisfied
    {
        if (m_minHeap)
            return m_data[parent] < m_data[current];
        else
            return m_data[parent] > m_data[current];
    }

    void swap(int first, int second)
    {
        T tmp = m_data[first]; // move wrap it?
        m_data[first] = m_data[second];
        m_data[second] = tmp;
    }

    T* m_data = nullptr;
    int m_currentSize = 0;
    int m_capacity = 0;
    bool m_minHeap = false;
};