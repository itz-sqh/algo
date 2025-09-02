#pragma once
#include <bits/stdc++.h>
#include "../Utils/Edge.h"

using namespace std;

struct LCA {
    // LCA with Binary Lifting
    // Time  : Preprocessing - O(n * log(n)), Query - O(log n)
    // Space : O(n * log(n))
    vector<vector<Edge>> graph;
    int vertexCount;
    const int root;
    vector<vector<int>> dp;
    vector<int> height;
    int maxK;
    bool built;

    LCA(const vector<vector<int>>& g, int root = 0) : vertexCount(g.size()), root(root) {
        graph.resize(vertexCount);
        for (int from = 0; from < vertexCount; from++)
            for (int to: g[from])
                addEdge(from, to);
        maxK = 0;
        while ((1 << maxK) <= vertexCount)
            maxK++;
        dp.resize(vertexCount, vector<int>(maxK + 1, -1));
        height.resize(vertexCount);
        build();
    }

    LCA(int vertexCount, int root = 0) : vertexCount(vertexCount), root(root), built(false) {
        graph.resize(vertexCount);
        maxK = ceil(log2(vertexCount)) + 1;
        dp.resize(vertexCount, vector<int>(maxK + 1, -1));
        height.resize(vertexCount);
    }

    void addEdge(int from, int to, int weight = 1) {
        graph[from].emplace_back(from, to, weight);
        graph[to].emplace_back(to, from, weight);
    }

    void build() {
        if (built)
            return;
        dfs(root, root, 0);
        for (int k = 1; k <= maxK; k++)
            for (int u = 0; u < vertexCount; u++)
                if (dp[u][k - 1] != -1)
                    dp[u][k] = dp[dp[u][k - 1]][k - 1];
        built = true;
    }

    void dfs(int current, int parent, int h) {
        dp[current][0] = parent;
        height[current] = h;
        for (const Edge& edge: graph[current]) {
            if (edge.to != parent)
                dfs(edge.to, current, h + 1);
        }
    }

    int get(int u, int v) {
        if (!built)
            build();
        if (height[u] > height[v])
            swap(u, v);
        for (int k = maxK; k >= 0; k--)
            if (height[u] <= height[v] - (1 << k))
                v = dp[v][k];
        if (u == v)
            return u;

        for (int k = maxK; k >= 0; k--) {
            if (dp[u][k] != dp[v][k]) {
                u = dp[u][k];
                v = dp[v][k];
            }
        }
        return dp[u][0];
    }
};
