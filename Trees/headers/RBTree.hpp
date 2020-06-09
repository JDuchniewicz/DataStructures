#pragma once

#include <iostream>

enum class eColor
{
    BLACK = 0,
    RED
};

template<typename T>
struct RBNode
{
    RBNode() {}
    RBNode(T d, eColor c, RBNode<T>* l, RBNode<T>* r, RBNode<T>* p) :
         data(d), color(c), left(l), right(r), parent(p) {}
    ~RBNode()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }

    T data;
    eColor color = eColor::BLACK;
    RBNode<T>* left = nullptr;
    RBNode<T>* right = nullptr;
    RBNode<T>* parent = nullptr;
};

template<typename T>
class RBTree
{
public:
    RBTree()
    {
        m_nullNode = new RBNode<T>();
        m_nullNode->color = eColor::BLACK;
        m_root = m_nullNode;
    }

    ~RBTree()
    {
        if (m_root != m_nullNode) // unpin null node from all leaves
        {
            cleanUpNulls(m_root);
            delete m_root; // recursively remove left and right children
        }
        delete m_nullNode;
    }

    void insert(T data)
    {
        RBNode<T>* parent = nullptr;
        RBNode<T>* current = m_root;

        while (current != m_nullNode)
        {
            parent = current;
            if (data < current->data) // here inject comparison
                current = current->left;
            else
                current = current->right;
        }
        RBNode<T>* newNode = new RBNode<T>();
        newNode->data = data;
        newNode->parent = parent;
        newNode->left = m_nullNode;
        newNode->right = m_nullNode;

        if (!parent)
            m_root = newNode;
        else if (newNode->data < parent->data) // comparison injection
            parent->left = newNode;
        else
            parent->right = newNode;

        newNode->color = eColor::RED;

        if (!parent) // it is a root node - hence black, no need to fix
        {
            newNode->color = eColor::BLACK;
            return;
        } else if (!parent->parent) // no grandparent, so no need to rebalance
            return;
            
        fixup(newNode);
    }

    bool remove(T data) // because we first have to find the required node, perform ordinary binary search
    {
        RBNode<T>* current = nullptr;
        RBNode<T>* toRemove = bSearch(data);
        RBNode<T>* y = toRemove;
        if (!toRemove) // failed to find the required node
            return false;

        eColor yOrigin = y->color; //original colour
        if (toRemove->left == m_nullNode) // either one of children does not exist (normal BST removal)
        {
            current = toRemove->right;
            transplant(toRemove, toRemove->right); // rightChild is now in toRemove's place
        }
        else if (toRemove->right == m_nullNode)
        {
            current = toRemove->left;
            transplant(toRemove, toRemove->left);
        }
        else // both exist
        {
            y = minChild(toRemove->right); // find smallest child to swap with
            yOrigin = y->color;
            current = y->right;
            if (y->parent == toRemove)
                current->parent = y;
            else
            {
                transplant(y, y->right);
                y->right = toRemove->right;
                y->right->parent = y;
            }

            transplant(toRemove, y);
            y->left = toRemove->left;
            y->left->parent = y;
            y->color = toRemove->color;

        }
        toRemove->left = nullptr; // need to unpin the children otherwise there will be double free's
        toRemove->right = nullptr;
        delete toRemove;
        if (yOrigin == eColor::BLACK)
            removeFixup(current);

        return true;
    }

    void printTree() const
    {
        if (m_root)
            printHelper(m_root, "", true);
    }

private:
    void printHelper(RBNode<T>* current, std::string indent, bool last) const
    {
        if (current != m_nullNode)
        {
            std::cout << indent;
            if (last)
            {
                std::cout << "R----";
                indent += "     ";
            }
            else
            {
                std::cout << "L----";
                indent += "|    ";
            }
            std::cout << current->data << "(" << ((current->color == eColor::BLACK) ? "BLACK" : "RED")<< ")" << std::endl;
            printHelper(current->left, indent, false);
            printHelper(current->right, indent, true);
        }
    }

    void leftRotate(RBNode<T>* x) // y is a child of x
    {
        RBNode<T>* y = x->right;
        x->right = y->left; // y's left subtree is x's right subtree

        if (y->left != m_nullNode) // if it exists, fix the parent's pointer
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

    void rightRotate(RBNode<T>* x) // mirror but when y is a left subtree
    {
        RBNode<T>* y = x->left;
        x->left = y->right;

        if (y->right != m_nullNode)
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

    RBNode<T>* successor(RBNode<T>* current)
    {
        if (current->right != m_nullNode) // if there exists a direct right successor
        {
            current = current->right;
            while (current->left != m_nullNode) // try to find minval
                current = current->left;

            return current;
        }

        RBNode<T>* parent = current->parent;
        while (parent && current == parent->right) // find the parent for which it is still a right child, its parent is the successor
        {
            current = parent;
            parent = parent->parent;
        }

        return parent;
    }

    RBNode<T>* predecessor(RBNode<T>* current)
    {
        RBNode<T>* predec = nullptr;
        if (current->left != m_nullNode) // if there is a left subtree, predecessor is the rightmost node in the left subtree
        {
            predec = current->left;
            while (predec->right != m_nullNode)
                predec = predec->right;

            return predec;
        }
        predec = current->parent;
        while (predec && current == predec->left) // else it is analoguous, go up the tree and the parent will be prede
        {
            current = predec;
            predec = predec->parent;
        }

        return predec;
    }

    void transplant(RBNode<T>* what, RBNode<T>* with) // replace node's pointers before it is deleted
    {
        if (!what->parent) // if root node is removed
            m_root = with;
        else if (what == what->parent->left) // if it is left node of its parent
            what->parent->left = with;
        else
            what->parent->right = with; // same with right

        with->parent = what->parent; // finally replace parent ownership
    }

    RBNode<T>* minChild(RBNode<T>* current) const
    {
        while (current->left != m_nullNode)
            current = current->left;
        return current;
    }

    void removeFixup(RBNode<T>* current) // special fix up because of remove
    {
        RBNode<T>* sibling = nullptr;
        while (current != m_root && current->color == eColor::BLACK)
        {
            if (current == current->parent->left) // if is a left child
            {
                sibling = current->parent->right; // a right sibling
                if (sibling->color == eColor::RED)
                {
                    sibling->color = eColor::BLACK; //mark it black
                    current->parent->color = eColor::RED; // parent of both is red
                    leftRotate(current->parent); // rotate so that now sibling is at the 'top'
                    sibling = current->parent->right; // there is a new sibling now because current went down - rotate migrated it
                }
                if (sibling->left->color == eColor::BLACK && sibling->right->color == eColor::BLACK) // if both children of sibling are black
                {
                    sibling->color = eColor::RED; // it will now be red, both parents black
                    current = current->parent; // move up and rerun the loop
                }
                else
                {
                    if (sibling->right->color == eColor::BLACK) // just the right child of sibling is black
                    {
                        sibling->left->color = eColor::BLACK; // switch colours in both left child and sibling
                        sibling->color = eColor::RED;
                        rightRotate(sibling); // now left child is the new sibling (we lose sibling validity)
                        sibling = current->parent->right; // repair sibling's pointer
                    }
                    // now right child of sibling is for sure red
                    sibling->color = current->parent->color; // colour the sibling the same color as parent
                    current->parent->color = eColor::BLACK; // both 
                    sibling->right->color = eColor::BLACK;
                    leftRotate(current->parent); // sibling is now the top of subtree
                    current = m_root; // finished rebalancing, satisfy loop condition
                }
            }
            else // it is a right child
            {
                sibling = current->parent->left;
                if (sibling->color == eColor::RED)
                {
                    sibling->color = eColor::BLACK;
                    current->parent->color = eColor::RED;
                    rightRotate(current->parent); // same rotation as in left but now right
                    sibling = current->parent->left; // rotate migrated current
                }
                if (sibling->left->color == eColor::BLACK && sibling->right->color == eColor::BLACK)
                {
                    sibling->color = eColor::RED;
                    current = current->parent;
                }
                else
                {
                    if (sibling->left->color == eColor::BLACK)
                    {
                        sibling->right->color = eColor::BLACK;
                        sibling->color = eColor::RED;
                        leftRotate(sibling);
                        sibling = current->parent->left;
                    }

                    sibling->color = current->parent->color;
                    current->parent->color = eColor::BLACK;
                    sibling->left->color = eColor::BLACK;
                    rightRotate(current->parent);
                    current = m_root;
                }
            }

        }
        current->color = eColor::BLACK; // finally mark it as black (root)
    }

    void fixup(RBNode<T>* newNode) // fix the tree up from newNode
    {
        RBNode<T>* uncle = nullptr;
        while (newNode->parent->color == eColor::RED) // what about nullptr?
        {
            if (newNode->parent == newNode->parent->parent->right) // if parent is a right child of its grandparent
            {
                uncle = newNode->parent->parent->left; // uncle
                if (uncle->color == eColor::RED) // if uncle is red
                {
                    uncle->color = eColor::BLACK; // it becomes black
                    newNode->parent->color = eColor::BLACK; // parent is black as well
                    newNode->parent->parent->color = eColor::RED; // grandparent is red now and both its children (parent and uncle) are black
                    newNode = newNode->parent->parent; // move up to the grandparent and check if it is violated again, i.e. its direct parent is also red!
                }
                else // uncle is black
                {
                    if (newNode == newNode->parent->left) // left child
                    {
                        newNode = newNode->parent;
                        rightRotate(newNode); // parent is now right child
                    }
                    newNode->parent->color = eColor::BLACK;
                    newNode->parent->parent->color = eColor::RED;
                    leftRotate(newNode->parent->parent); // rotate at grandparent
                }
            }
            else
            {
                uncle = newNode->parent->parent->right; // mirror case for right
                if (uncle->color == eColor::RED)
                {
                    uncle->color = eColor::BLACK;
                    newNode->parent->color = eColor::BLACK;
                    newNode->parent->parent->color = eColor::RED;
                    newNode = newNode->parent->parent;
                }
                else
                {
                    if (newNode == newNode->parent->right)
                    {
                        newNode = newNode->parent;
                        leftRotate(newNode);
                    }
                    newNode->parent->color = eColor::BLACK;
                    newNode->parent->parent->color = eColor::RED;
                    rightRotate(newNode->parent->parent);
                }
            }
            if (newNode == m_root)
                break;
        }
        m_root->color = eColor::BLACK; // fix root's colour
    }

    RBNode<T>* bSearch(T data) const
    {
        RBNode<T>* current = m_root;
        while (current != m_nullNode)
        {
            if (current->data == data)
                return current;
            else if (data < current->data) // comparison injection
                current = current->left;
            else if (data > current->data)
                current = current->right;
        }
        return nullptr;  // not found!
    }

    void cleanUpNulls(RBNode<T>* current)
    {
        if (current->left == m_nullNode)
            current->left = nullptr;
        else
            cleanUpNulls(current->left);
            
        if (current->right == m_nullNode)
            current->right = nullptr;
        else
            cleanUpNulls(current->right);
    }

    RBNode<T>* m_root = nullptr; // need to add the special node and take care of deleting it in a proper way TODO:!
    RBNode<T>* m_nullNode = nullptr;
};