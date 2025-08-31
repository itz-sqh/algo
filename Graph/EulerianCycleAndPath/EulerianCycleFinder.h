#pragma once
#include <bits/stdc++.h>

using namespace std;

struct EulerianFinder{
    vector<unordered_multiset<int>> graph;
    vector<int> inDegree, outDegree;
    vector<bool> visited;
    vector<int> path;
    int vertexCount{};
    int edgeCount{};
    bool isDirected;

    EulerianFinder(const vector<vector<int>>& graph, bool directed)
        :isDirected(directed),graph(graph.size()){
        vertexCount = graph.size();
        inDegree.assign(vertexCount, 0);
        outDegree.assign(vertexCount, 0);
        visited.assign(vertexCount, false);

        for (int u = 0; u < vertexCount; u++){
            for (int v : graph[u]){
                outDegree[u]++;
                inDegree[v]++;
                edgeCount++;
            }
        }
        if (!isDirected) edgeCount /= 2;
    }

    bool hasEulerianCycle() const{}

    bool hasEulerianPath() const{}

    int findStartVertex() const{}

    void dfs(int u, vector<int>& tempPath){}

    vector<int> findEulerianPath(){}

    vector<int> findEulerianCycle(){}
};
