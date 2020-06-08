#pragma once

#include <vector>
#include <random>

// for randomisation (global variables yuck)
std::random_device g_rd;
std::mt19937 g_rng(g_rd{});

template<typename T, typename N>
struct Node
{
    Node(T d) : data(d) {};

    ~Node()
    {
        for (auto* c : children)
            delete c;
    }

    void add(T v)
    {
        // call add on a child until one subchild can accept it (it will favor the left subtree)
        if (children.size() == maxSize) // very poor randomisation
        {
            int randIdx = distr(g_rng);
            children.at(randIdx)->add(v);
        }
        else
            children.push_back({ v });
    }

    bool remove(T v)
    {

    }

    static N maxSize;
    static std::uniform_int_distribution<T> distr(0, maxSize - 1);
    T data;
    std::vector<Node<T, N>*> children; // it should be array
};

// this is not a search tree, nodes are added randomly, until a level is filled
// because this is not ordered, it is very ineffective
template<typename T, typename N>
class Nary
{
public:
    Nary()
    {
        m_root = nullptr;
    }

    ~Nary()
    {
        delete m_root;
    }

    void add(T v)
    {
        m_root.add(v);
    }

    bool remove(T v)
    {
        return m_root.remove(v);
    }

    int height() const
    {
        return height(m_root);
    }
private:
    int height(Node<T, N>* current) const
    {
        if (!current)
            return 0;
        
        int maxHeight = 0;
        for (auto c : current->children)
            maxHeight = std::max(height(c), maxHeight);

        return 1 + maxHeight;
    }

    Node<T, N>* m_root;
};