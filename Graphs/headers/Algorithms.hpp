#pragma once

#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <iostream>
#include <climits>

// BFS and DFS algorithms for adajcency matrices (recursive and iterative)
// this all can be generalized for a node from which we start, but then adjacency lists need modifications per each new type

void iterativeDFS(const std::vector<std::vector<int>>& adj, int start)
{
    bool* visited = new bool[adj.size()];
    std::stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int current = s.top();
        s.pop();

        if (!visited[current])
        {
            std::cout << current << " " << std::endl;
            visited[current] = true; // mark it as visited only after popping

            for (auto c : adj[current]) // should this be called just once? CHECK IT
                if (!visited[c])
                    s.push(c);
        }
    }
    delete[] visited;
}

void DFSUtil(const std::vector<std::vector<int>>& adj, bool visited[], int current)
{
    std::cout << current << " " << std::endl;
    visited[current] = true;

    for (size_t i = 1; i < adj[current].size(); ++i)
        if (!visited[adj[current][i]])
            DFSUtil(adj, visited, adj[current][i]);
}

void recursiveDFS(const std::vector<std::vector<int>>& adj, int start)
{
    bool* visited = new bool[adj.size()];
    
    for (size_t i = 1; i < adj.size(); ++i)
        if (!visited[i])
            DFSUtil(adj, visited, i);

    delete[] visited;
}

void iterativeBFS(const std::vector<std::vector<int>>& adj, int start)
{
    bool* visited = new bool[adj.size()];
    std::queue<int> q;
    q.push(start);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (!visited[current])
        {
            std::cout << current << " " << std::endl;
            visited[current] = true;
        }

        for (auto c : adj[current])
            if (!visited[c])
                q.push(c);
    }
    delete[] visited;
}

// a recursive BFS is pointless because it does not utilize stack :)
// Adjacency Matrix implementations

// Weighted graph algorithms
void Dijkstra(const std::vector<std::vector<std::pair<int,int>>>& adj, int start)
{
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq; // priority-queue of distance-from-source:edge pairs, with a custom comparison by distance-from-source
    std::vector<int> distance(adj.size(), INT_MAX);
    distance[start] = 0;

    pq.push({0, start});
    while (!pq.empty())
    {
        auto current = pq.top();
        int u = current.second;
        pq.pop();

        for (auto& [v, weight]: adj[u])
        {
            // new distance is equal to distance to the current node + from current node to this neighbor
            if (distance[v] > distance[u] + weight)
            {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v}); // push the visited node with updated cost ( we could have just found a better path!)
            }
        }
    }

    // can either return or print it:
    std::cout << "Printing Dijkstra results (shortest path from source): " << std::endl;
    for (size_t i = 1; i < adj.size(); ++i)
        std::cout << "i: " << i << " distance: " << distance[i] << " ";
    std::cout << std::endl;
}