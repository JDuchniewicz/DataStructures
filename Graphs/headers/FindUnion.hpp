#pragma once

#include <unordered_map>

// the easiest to implement version of FindUnion
class FindUnion
{
public:
    int find(int x)
    {
        int root = x;
        while (parents[root] != root)
        {
            root = parents[root];
        }
        return root;
    }

    void merge(int x, int y)
    {
        int p1 = find(x);
        int p2 = find(y);
        if (parents[p1] == parents[p2])
            return;
        if (sizes[p1] > sizes[p2])
        {
            parents[p2] = p1;
            sizes[p1] += sizes[p2];
            if (sizes[p1] > max)
                max = sizes[p1];
        }
        else
        {
            parents[p1] = p2;
            sizes[p2] += sizes[p1];
            if (sizes[p2] > max)
                max = sizes[p2];
        }
    }

    bool connected(int x, int y) const
    {
        return find(x) == find(y);
    }

    int size(int x)
    {
        return sizes[find(x)];
    }

    int max = 0;
    std::unordered_map<int, int> parents;
    std::unordered_map<int, int> sizes;
};