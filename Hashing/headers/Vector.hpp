#pragma once

template<typename T>
class Vector
{
public:
    Vector()
    {
        m_size = 0;
        m_capacity = 2;
        m_data = new T[m_capacity];
    }

    ~Vector()
    {
        delete[] m_data;
    }

    void push(T element)
    {
        if (m_size == m_capacity)
            resize();
        m_data[m_size++] = element;
    }

    bool erase(T element)
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (m_data[i] == element)
            {
                for (int j = i; j < m_size; ++j)
                    m_data[j] = m_data[j + 1]; // shift all elements left
                --m_size;
                return true;
            }
        }
        return false;
    }

    void resize()
    {
        m_capacity *= 2;
        T* tmp = new T[m_capacity];
        for (int i = 0; i < m_size; ++i)
            tmp[i] = m_data[i];
        
        delete[] m_data;
        m_data = tmp;
    }

    int contains(T element) const
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (m_data[i] == element)
                return i;
        }
        return -1;
    }

    T at(int idx) const
    {
        return m_data[idx];
    }

    bool isEmpty() const
    {
        return m_size == 0;
    }

    int size() const
    {
        return m_size;
    }
    
    int capacity() const
    {
        return m_capacity;
    }

private:
    T* m_data = nullptr;
    int m_size = 0;
    int m_capacity = 0;
};