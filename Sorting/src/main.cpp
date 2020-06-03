/*
    Various sorting algorithm implementations
*/
#include <HeapSort.hpp>
#include <MergeSort.hpp>
#include <InsertionSort.hpp>
#include <QuickSort.hpp>
#include <algorithm>
#include <numeric>

constexpr int arraySize = 10;
constexpr int algoChoice = 5;

int main()
{
    int data[arraySize];
    std::iota(std::begin(data), std::end(data), 1);
    std::random_shuffle(std::begin(data), std::end(data));
    Heap<int> minHeap{ arraySize, true };
    Heap<int> maxHeap{ arraySize, false };

    if constexpr (algoChoice == 0) // heap sort
    {
        for (int i = 0; i < arraySize; ++i)
        {
            minHeap.push(data[i]);
            maxHeap.push(data[i]);
        }
        
        minHeap.display();
        maxHeap.display();

        std::cout << std::endl << "Extracting min: " << std::endl;
        while (!minHeap.isEmpty())
            std::cout << minHeap.pop() << " ";

        std::cout << std::endl << "Extracting max: " << std::endl;
        while (!maxHeap.isEmpty())
            std::cout << maxHeap.pop() << " ";

        minHeap.display();
        maxHeap.display();
        // add remove testing!
        // test for non-trivial types
    }
    else if constexpr (algoChoice == 1) // recursive merge sort
    {
        recursiveMergeSort(data, 0, arraySize - 1);
    } else if constexpr (algoChoice == 2) // iterative merge sort
    {
        iterativeMergeSort(data, arraySize);
    } else if constexpr (algoChoice == 3) // insertion sort
    {
        insertionSort(data, arraySize);
    } else if constexpr (algoChoice == 4) // recursive quicksort
    {
        recursiveQuickSort(data, 0, arraySize - 1);
    } else if constexpr (algoChoice == 5) // iterative quicksort
    {
        iterativeQuickSort(data, 0, arraySize - 1);
    }

    std::cout << "Sorted array: " << std::endl;
    for (int i = 0; i < arraySize; ++i)
        std::cout << data[i] << " ";
    return 0;
}