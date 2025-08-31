#pragma once
#include <bits/stdc++.h>

using namespace std;

struct LCA{
    const vector<vector<int>> graph;
    int vertexCount;
    const int root;
    vector<vector<int>> dp;
    vector<int> height;
    int maxK;

    LCA(const vector<vector<int>>& graph, int root) : graph(graph), root(root), maxK(0){
        vertexCount = graph.size();
        while ((1 << maxK) < vertexCount)
            maxK++;
        dp.resize(graph.size(), vector(maxK + 1, 0));
        height.resize(graph.size());
        dfs(root, root, 0);
        for (int k = 1; k <= maxK; k++)
            for (int u = 0; u < vertexCount; u++)
                dp[u][k] = dp[dp[u][k - 1]][k - 1];
    }

    void dfs(int current, int parent, int h){
        dp[current][0] = parent;
        height[current] = h;
        for (int to : graph[current]){
            if (to != parent)
                dfs(to, current, h + 1);
        }
    }


    int get(int u, int v) const{
        if (height[u] > height[v]) swap(u, v);
        for (int k = maxK; k >= 0; k--)
            if (height[u] <= height[v] - (1 << k))
                v = dp[v][k];
        if (u==v) return u;
        int res = root;
        for (int k = maxK; k >= 0; k--){
            if (dp[u][k] != dp[v][k])
                break;
            res = dp[u][k];
        }
        return res;
    }
};
