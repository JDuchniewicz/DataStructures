#include <BST.hpp>
#include <Trie.hpp>
#include <RBTree.hpp>

constexpr int algoChoice = 2;

void testTree()
{
    BST<int> binaryTree;
    std::cout << "Adding to BST" << std::endl;
    binaryTree.add(1);
    binaryTree.add(8);
    binaryTree.add(3);
    binaryTree.add(5);
    binaryTree.add(7);
    binaryTree.add(6);
    binaryTree.add(4);

    std::cout << "Adding duplicate values" << std::endl;
    binaryTree.add(4);
    binaryTree.add(4);

    binaryTree.printPreOrder();
    binaryTree.printInOrder();
    binaryTree.printPostOrder();
    binaryTree.printLevelOrder();
    binaryTree.printPreOrderIterative();
    binaryTree.printInOrderIterative();
    binaryTree.printPostOrderIterative();
    std::cout << "Height is: " << binaryTree.height() << std::endl;
    int min = 0, max = 0;
    if (binaryTree.findMin(min))
        std::cout << "Min is: " << min << std::endl;
    if (binaryTree.findMax(max))
        std::cout << "Max is: " << max << std::endl;
    
    std::cout << "Removing from BST" << std::endl;
    binaryTree.remove(3);
    binaryTree.remove(1);

    binaryTree.printPreOrder();
    binaryTree.printInOrder();
    binaryTree.printPostOrder();
    binaryTree.printLevelOrder();
    std::cout << "Height is: " << binaryTree.height() << std::endl;
    if (binaryTree.findMin(min))
        std::cout << "Min is: " << min << std::endl;
    if (binaryTree.findMax(max))
        std::cout << "Max is: " << max << std::endl;

    std::cout << "Removing nonexistent from BST" << std::endl;
    binaryTree.remove(3);
    binaryTree.remove(1);

    binaryTree.printPreOrder();
    binaryTree.printInOrder();
    binaryTree.printPostOrder();
    binaryTree.printLevelOrder();
    std::cout << "Height is: " << binaryTree.height() << std::endl;
    if (binaryTree.findMin(min))
        std::cout << "Min is: " << min << std::endl;
    if (binaryTree.findMax(max))
        std::cout << "Max is: " << max << std::endl;
}

void testTrie()
{
    std::cout << "Trie insertion" << std::endl;
    Trie trie;
    trie.insert("they");
    trie.insert("their");
    trie.insert("amazing");
    trie.insert("amaze");
    trie.insert("amass");
    trie.insert("massive");

    std::cout << "Trie checking" << std::endl; // covers case -> is a string a substring?
    std::cout << "Is 'they'?: " << trie.search("they") << std::endl;
    std::cout << "Is 'their'?: " << trie.search("their") << std::endl;
    std::cout << "Is 'amazing'?: " << trie.search("amazing") << std::endl;
    std::cout << "Is 'amaze'?: " << trie.search("amaze") << std::endl;
    std::cout << "Is 'amass'?: " << trie.search("amass") << std::endl;
    std::cout << "Is 'massive'?: " << trie.search("massive") << std::endl;
    std::cout << "Is 'steph'?: " << trie.search("steph") << std::endl;
}

void testRBTree()
{
    std::cout << "RBTree insertion" << std::endl;
    RBTree<int> tree;
    std::cout << "Inserting 1" << std::endl;
    tree.insert(1);
    tree.printTree();
    std::cout << "Inserting 2" << std::endl;
    tree.insert(2);
    tree.printTree();
    std::cout << "Inserting 3" << std::endl;
    tree.insert(3);
    tree.printTree();
    std::cout << "Inserting 4" << std::endl;
    tree.insert(4);
    tree.printTree();
    std::cout << "Inserting 5" << std::endl;
    tree.insert(5);
    tree.printTree();
    std::cout << "Inserting 6" << std::endl;
    tree.insert(6);
    tree.printTree();

    std::cout << "RBTree removal" << std::endl;
    std::cout << "Removing 2" << std::endl;
    tree.remove(2);
    tree.printTree();
    std::cout << "Removing 3" << std::endl;
    tree.remove(3);
    tree.printTree();
    std::cout << "Removing 5" << std::endl;
    tree.remove(5);
    tree.printTree();
    std::cout << "Removing Nonexistent" << std::endl;
    std::cout << "Success: " << tree.remove(50) << std::endl;
    tree.printTree();
    std::cout << "Removing 1" << std::endl;
    tree.remove(1);
    tree.printTree();
    std::cout << "Removing 4" << std::endl;
    tree.remove(4);
    tree.printTree();
    std::cout << "Removing 6" << std::endl;
    tree.remove(6);
    tree.printTree();
}

int main()
{
    if constexpr (algoChoice == 0) // BST
        testTree();
    else if constexpr (algoChoice == 1) // Trie
        testTrie();
    else if constexpr (algoChoice == 2) // RBTree
        testRBTree();
    return 0;
}