#include <Algorithms.hpp>

constexpr int algoChoice = 2;

std::vector<std::vector<int>> buildAdjListGraph() // build either directed or bidirected graph
{
    std::vector<std::vector<int>> adj;
    // add 9 nodes so size is 10
    for (int i = 0; i < 10; ++i)
        adj.push_back({ });
        
    // add 1
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(3);
    adj[3].push_back(1);

    // add 2
    adj[2].push_back(7);
    adj[7].push_back(2);
    adj[2].push_back(3);
    adj[3].push_back(2);

    // add 3
    adj[3].push_back(4);
    adj[4].push_back(3);
    adj[3].push_back(5);
    adj[5].push_back(3);

    // add 4
    adj[4].push_back(7);
    adj[7].push_back(4);
    adj[4].push_back(8);
    adj[8].push_back(4);

    // add 5,6
    adj[5].push_back(6);
    adj[6].push_back(5);
    
    // 7 is already connected
    // add 8 and 9
    adj[8].push_back(9);
    adj[9].push_back(8);

    // build graph
    return adj;
}

std::vector<std::vector<int>> buildAdjMatrixGraph()
{
    std::vector<std::vector<int>> adj;
    
    // build graph
    return adj;
}

int main()
{
    std::vector<std::vector<int>> adjacencyList = buildAdjListGraph();
    std::vector<std::vector<int>> adjacencyMatrix = buildAdjMatrixGraph();
    if constexpr (algoChoice == 0)
        recursiveDFS(adjacencyList, 1);
    else if (algoChoice == 1)
        iterativeDFS(adjacencyList, 1);
    else if (algoChoice == 2)
        iterativeBFS(adjacencyList, 1);
    //else if (algoChoice == 3)
    //    testRecursiveMatrixDFS();
    return 0;
}