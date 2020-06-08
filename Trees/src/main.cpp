#include <BST.hpp>

int main()
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
    return 0;
}