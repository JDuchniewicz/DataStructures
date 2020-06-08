#pragma once

#include <iostream>
#include <queue>

/* A recursive BST implementation */

template<typename T>
struct Node
{
    Node(T d, Node<T>* l, Node<T>* r) : data(d), left(l), right(r) {};

    ~Node()
    {
        delete left;
        delete right;
    }

    T data;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
};

template<typename T>
class BST
{
public:
    BST()
    {
        m_root = nullptr;
    }

    ~BST()
    {
        delete m_root;
    }

    void add(T v)
    {
        m_root = addRecursive(m_root, v);
    }

    void remove(T v) // check it (will clear root for nonexistent values..) // TODO: FIXIT
    {
        m_root = removeRecursive(m_root, v);
    }

    bool find(T v)
    {
        return findRecursive(m_root, v);
    }

    bool findMax(T& valOut) const
    {
        Node<T>* current = findMaxRecursive(m_root);
        if (!current)
            return false;

        valOut = current->data;    
        return true;
    }

    bool findMin(T& valOut) const
    {
        Node<T>* current = findMinRecursive(m_root);
        if (!current)
            return false;

        valOut = current->data;    
        return true;
    }

    int height() const
    {
        return height(m_root);
    }

    int size() const
    {
        return size(m_root);
    }

    void printPreOrder() const
    {
        std::cout << "Pre order printing of the tree " << std::endl;
        printPreOrder(m_root);
        std::cout << std::endl; 
    }
    
    void printInOrder() const
    {
        std::cout << "In order printing of the tree " << std::endl;
        printInOrder(m_root);
        std::cout << std::endl; 
    }

    void printPostOrder() const
    {
        std::cout << "Post order printing of the tree " << std::endl;
        printPostOrder(m_root);
        std::cout << std::endl; 
    }

    void printLevelOrder() const
    {
        std::cout << "Post order printing of the tree " << std::endl;
        printLevelOrder(m_root);
        std::cout << std::endl; 
    }

private:
    Node<T>* addRecursive(Node<T>* current, T v)
    {
        if (!current)
            current = new Node<T>(v, nullptr, nullptr);
        else if (v < current->data)
            current->left = addRecursive(current->left, v);
        else if (v > current->data)
            current->right = addRecursive(current->right, v);
        return current;
    }

    Node<T>* removeRecursive(Node<T>* current, T v)
    {
        if (!current)
            return nullptr;
        else if (v < current->data)
            current->left = removeRecursive(current->left, v);
        else if (v > current->data)
            current->right = removeRecursive(current->right, v);
        else if (current->left && current->right) // have both children, swap with smallest right child
        {
            Node<T>* temp = findMinRecursive(current->right); // find smallest child in right subtree
            current->data = temp->data; //swap data
            current->right = removeRecursive(current->right, current->data); // delete the child with swapped out data, in the right subtree
        }
        else // has either one of children, swap with it and delete the offspring
        {
            Node<T>* temp = current;
            if (!current->left)
                current = current->right;
            else if (!current->right)
                current = current->left;

            // to prevent recursive destruction of still chained children
            temp->left = nullptr;
            temp->right = nullptr; 
            delete temp;
        }
        return current;
    }

    Node<T>* findMinRecursive(Node<T>* current) const
    {
        if (!current)
            return nullptr;
        else if (!current->left)
            return current;
        else
            return findMinRecursive(current->left);
    }

    Node<T>* findMaxRecursive(Node<T>* current) const
    {
        if (!current)
            return nullptr;
        else if (!current->right)
            return current;
        else
            return findMaxRecursive(current->right);
    }

    bool findRecursive(Node<T>* current, T v) const
    {
        if (!current)
            return false;
        else if (v == current->data)
            return true;
        else if (v < current->data)
            return findRecursive(current->left, v);
        else if (v > current->data) 
            return findRecursive(current->right, v);
    }

    int size(Node<T>* current) const
    {
        if (!current)
            return 0;
        return size(current->left) + 1 + size(current->right);
    }

    int height(Node<T>* current) const
    {
        if (!current)
            return 0;

        int lheight = height(current->left);
        int rheight = height(current->right);

        if (lheight > rheight)
            return lheight + 1;
        else
            return rheight + 1;
    }

    void printInOrder(Node<T>* current) const
    {
        if (!current)
            return;
        printInOrder(current->left);
        std::cout << current->data << " ";
        printInOrder(current->right);
    }

    void printPreOrder(Node<T>* current) const
    {
        if (!current)
            return;
        std::cout << current->data << " ";
        printPreOrder(current->left);
        printPreOrder(current->right);
    }

    void printPostOrder(Node<T>* current) const
    {
        if (!current)
            return;
        printPostOrder(current->left);
        printPostOrder(current->right);
        std::cout << current->data << " ";
    }

    void printLevelOrder(Node<T>* current) const
    {
        if (!current)
            return;
        
        // use BFS with level marking
        std::queue<Node<T>*> q;
        q.push(current);
        while (!q.empty())
        {
            int nodeCount = q.size(); // number of nodes at current level

            while (nodeCount >  0)
            {
                current = q.front();
                q.pop();
                std::cout << current->data << " ";
                if (current->left)
                    q.push(current->left);
                if (current->right)
                    q.push(current->right);

                --nodeCount;
            }
            std::cout << std::endl;
        }
    }

    Node<T>* m_root = nullptr;
};