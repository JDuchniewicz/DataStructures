#include <Algorithms.hpp>
#include <Graphs.hpp>
#include <deque>

constexpr int algoChoice = 3;

AdjGraph buildAdjListGraph(int N, bool isBiDirectional) // build either directed or bidirected graph
{
    std::vector<Edge> edges = {
        {1, 2}, {1, 3}, {2, 7}, {2, 3}, {3, 4}, {3, 5}, {4, 7}, {4, 8}, {5, 6}, {8, 9}
    };
    return {edges, N, isBiDirectional};
}

AdjWeightedGraph buildAdjWeightedGraph(int N, bool isBiDirectional)
{
    std::vector<WEdge> edges = {
        {1, 2, 3}, {1, 3, 2}, {2, 7, 4}, {2, 3, 1}, {3, 4, 2}, {3, 5, 5}, {4, 7, 2}, {4, 8, 1}, {5, 6, 8}, {8, 9, 3}, {4, 5, 1}, {1, 10, 1}, {3, 10, 2}, {5, 10, 15}
    };
    return {edges, N, isBiDirectional};

}

std::deque<std::deque<bool>> buildAdjMatrixGraph()
{
    std::deque<std::deque<bool>> matrix;
    
    // build graph
    return matrix;
}

std::vector<std::vector<std::pair<int,int>>> buildWeightedAdjListGraph()
{
    std::vector<std::vector<std::pair<int,int>>> adj;

    return adj;
}

int main()
{
    AdjGraph biAdjGraph = buildAdjListGraph(10, true);
    AdjWeightedGraph biAdjWeightedGraph = buildAdjWeightedGraph(11, true);
    std::deque<std::deque<bool>> adjacencyMatrix = buildAdjMatrixGraph();
    if constexpr (algoChoice == 0)
        recursiveDFS(biAdjGraph.adjList, 1);
    else if (algoChoice == 1)
        iterativeDFS(biAdjGraph.adjList, 1);
    else if (algoChoice == 2)
        iterativeBFS(biAdjGraph.adjList, 1);
    else if (algoChoice == 3)
        Dijkstra(biAdjWeightedGraph.adjList, 1);
    //else if (algoChoice == 3)
    //    testRecursiveMatrixDFS();
    return 0;
}