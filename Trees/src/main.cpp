#include <BST.hpp>
#include <Trie.hpp>

constexpr int algoChoice = 1;

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

int main()
{
    if constexpr (algoChoice == 0) // BST
        testTree();
    else if constexpr (algoChoice == 1) // Trie
        testTrie();
    return 0;
}