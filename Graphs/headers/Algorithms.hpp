#pragma once

#include <vector>
#include <stack>
#include <queue>
#include <iostream>

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
