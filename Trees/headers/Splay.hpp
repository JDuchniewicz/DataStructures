#pragma once

template<typename T>
struct SNode
{
    SNode()
    {

    }

    ~SNode()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }

    T data;
    SNode<T>* parent = nullptr;
    SNode<T>* left = nullptr;
    SNode<T>* right = nullptr;
};

template<typename T>
class SplayTree
{
public:
    SplayTree()
    {
        m_root = nullptr;
    }

    ~SplayTree()
    {
        delete m_root;
    }

    void insert(T val)
    {
        SNode<T>* current = m_root;
        SNode<T>* parent = nullptr;
        while (current)
        {
            parent = current;
            if (val < current->data)
                current = current->left;
            else
                current = current->right;
        }
        
        SNode<T>* newNode = new SNode<T>();
        newNode->data = val;
        newNode->parent = parent;

        if (!parent)
            m_root = newNode;
        else if (newNode->data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        splay(newNode); // bring it up top
    }

    bool remove(T val)
    {
        SNode<T>* current = searchTree(val);
        SNode<T>* sTree = nullptr;
        SNode<T>* tTree = nullptr;
        if (!current)
            return false;

        split(current, sTree, tTree);  // sTree will have empty right nodes
        if (sTree->left) // remove current from the root of s
            sTree->left->parent = nullptr;
        m_root = join(sTree->left, tTree); // extracted old root, now join left subnode with tree

        sTree->left = nullptr;
        delete sTree;
        return true;
    }

    bool search(T val)
    {
        SNode<T>* current = searchTree(val);
        if (current)
        {
            splay(current); // bring it to top
            return true;
        }
        return false;
    }

    void printTree() const
    {
        printHelper(m_root, "", true);
    }

private:
    void printHelper(SNode<T>* current, std::string indent, bool last) const
    {
        if (current)
        {
            std::cout << indent;
            if (last)
            {
                std::cout << "└────";
                indent += "     ";
            }
            else
            {
                std::cout << "├────";
                indent += "     ";
            }
            std::cout << current->data << std::endl;
            printHelper(current->left, indent, false);
            printHelper(current->right, indent, true);
        }
    }

    void splay(SNode<T>* current)
    {
        while (current->parent) // go up until it's root
        {
            if (!current->parent->parent) // if it is a root node
            {
                if (current == current->parent->left) // if it is a left child
                {
                    // zig
                    rightRotate(current->parent);
                } else
                {
                    // zag
                    leftRotate(current->parent);
                }
            } else if (current == current->parent->left && current->parent == current->parent->parent->left) // it and parent are both left children
            {
                // zig-zig
                rightRotate(current->parent->parent);
                rightRotate(current->parent);

            } else if (current == current->parent->right && current->parent == current->parent->parent->right)
            {
                // zag-zag
                leftRotate(current->parent->parent);
                leftRotate(current->parent);
            } else if (current == current->parent->left && current->parent == current->parent->parent->right)
            {
                // zag-zig
                rightRotate(current->parent);
                leftRotate(current->parent);
            } else 
            {
                // zig-zag
                leftRotate(current->parent);
                rightRotate(current->parent);
            }
        }
    }

    SNode<T>* join(SNode<T>* sTree, SNode<T>* tTree)
    {
        if (!sTree)
            return tTree;
        
        if (!tTree)
            return sTree;

        SNode<T>* x = max(sTree); // find the highest node in the source subtree
        splay(x);
        x->right = tTree; // reparent
        tTree->parent = x;
        return x;
    }

    void split(SNode<T>*& current, SNode<T>*& sTree, SNode<T>*& tTree)
    {
        splay(current); // move current to the top
        if (current->right)
        {
            tTree = current->right;
            tTree->parent = nullptr;
        }
        else
            tTree = nullptr;
        
        sTree = current;
        sTree->right = nullptr; // unpin the right subtree (it is distinct now)
        current = nullptr;
    }

    // TODO: group all common tree properties in a base class 
    void leftRotate(SNode<T>* x) // y is a child of x
    {
        SNode<T>* y = x->right;
        x->right = y->left; // y's left subtree is x's right subtree

        if (y->left) // if it exists, fix the parent's pointer
            y->left->parent = x;

        y->parent = x->parent; // fix the ascendant's pointer

        if (!x->parent) // if it is the root node
            m_root = y;
        else if (x == x->parent->left) // if x was a left child
            x->parent->left = y;
        else 
            x->parent->right = y;

        y->left = x; // finally fix parent-child relationship
        x->parent = y;
    }

    void rightRotate(SNode<T>* x) // mirror but when y is a left subtree
    {
        SNode<T>* y = x->left;
        x->left = y->right;

        if (y->right)
            y->right->parent = x;

        y->parent = x->parent;

        if (!x->parent)
            m_root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else 
            x->parent->right = y;
        
        y->right = x;
        x->parent = y;
    }

    SNode<T>* min(SNode<T>* current) const
    {
        while (current->left)
            current = current->left;
        
        return current;
    }

    SNode<T>* max(SNode<T>* current) const
    {
        while (current->right)
            current = current->right;
        
        return current;
    }

    SNode<T>* searchTree(T val) const
    {
        SNode<T>* current = m_root;
        while (current)
        {
            if (val < current->data)
                current = current->left;
            else if (val > current->data)
                current = current->right;
            else
                return current;
        }
        return nullptr;
    }

    SNode<T>* m_root = nullptr;
};