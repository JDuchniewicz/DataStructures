#pragma once

#include <vector>
#include <iostream>

struct Edge
{
    int src = 0, dest = 0;
};

struct WEdge
{
    int src = 0, dest = 0, weight = 0;
};

class AdjGraph
{
public:
    AdjGraph(const std::vector<Edge>& edges, int N, bool isBiDirectional = false)
    {
        adjList.resize(N);

        for (auto& [src, dest] : edges)
        {
            adjList[src].push_back(dest);
            if (isBiDirectional)
                adjList[dest].push_back(src);
        }
    }

    void print() const
    {
        for (size_t i = 0; i < adjList.size(); ++i)
        {
            // print all neighbors of a vertex
            for (auto& dest : adjList[i])
                std::cout << "(" << i << ", " << dest << ") ";
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<int>> adjList;
};

// assuming weights are the same both ways (if not a modification is needed)
class AdjWeightedGraph
{
public:
    AdjWeightedGraph(const std::vector<WEdge>& edges, int N, bool isBiDirectional = false)
    {
        adjList.resize(N);

        for (auto& [src, dest, weight] : edges)
        {
            adjList[src].push_back({dest, weight});
            if (isBiDirectional)
                adjList[dest].push_back({src, weight});
        }
    }

    void print() const
    {
        for (size_t i = 0; i < adjList.size(); ++i)
        {
            // print all neighbors of a vertex
            for (auto& [dest, weight] : adjList[i])
                std::cout << "(" << i << ", " << dest << ",W: " << weight << ") ";
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<std::pair<int,int>>> adjList;
};