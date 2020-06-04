#pragma once

#include <Vector.hpp>
#include <utility>
#include <iostream>

constexpr int MAXSIZE = 200; // smaller value, for bigger heap has to be used
constexpr int COLLSIZE = 10;

// all callers have to provide their own hashing function, this uses vector
template<typename K, typename H>
class Hashmap
{
public:
    Hashmap()
    {

    }

    ~Hashmap()
    {

    }

    void insert(K key)
    {
        int hash = m_hash(key);
        m_data[hash].push(key);
    }
    
    bool remove(K key)
    {
        int hash = m_hash(key);
        return m_data[hash].erase(key);
    }

private:
    Vector<K> m_data[MAXSIZE];
    H m_hash;
};


template<typename K, typename V, typename H>
class HashmapArray
{
public:
    HashmapArray()
    {
        for (int i = 0; i < MAXSIZE; ++i)
            for (int j = 0; j < COLLSIZE; ++j)
                m_data[i][j] = std::pair { -1, -1 };
    }

    ~HashmapArray()
    {

    }

    bool insert(K key, V value)
    {
        int hash = m_hash(key);

        for (int i = 0; i < COLLSIZE; ++i)
        {
            if (m_data[hash][i].first == -1) // this is not portable!
            {
                m_data[hash][i] = std::make_pair<K, V>( std::move(key), std::move(value) );
                return true;
            }
        }
        std::cout << "No space for given key " << key << std::endl;
        return false;
    }
    
    bool remove(K key)
    {
        int hash = m_hash(key);

        for (int i = 0; i < COLLSIZE; ++i)
        {
            if (m_data[hash][i].first == key) // this is not portable!
            {
                m_data[hash][i] = std::make_pair<K, V>( -1 , -1 );
                return true;
            }
        }
        return false;
    }

    V get(K key)
    {
        int hash = m_hash(key);

        for (int i = 0; i < COLLSIZE; ++i)
        {
            if (m_data[hash][i].first == key) // this is not portable!
                return m_data[hash][i].second;
        }
        return -1;
    }

private:
    std::pair<K,V> m_data[MAXSIZE][COLLSIZE];
    H m_hash;
};