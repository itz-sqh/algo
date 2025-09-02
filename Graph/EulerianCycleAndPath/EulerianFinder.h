#pragma once
#include <bits/stdc++.h>
#include "../Utils/Edge.h"

using namespace std;


struct EulerianFinder {
    // Check for and find Eulerian paths and cycles in directed or undirected graphs with self-loops and parallel edges
    // Time : check - O(n), find - O(m)   without copy graph [O(n+m)]
    // Space: check - O(1), find - O(n+m) without copy graph [O(n+m)]
    vector<vector<Edge>> graph;
    vector<int> inDegree, outDegree;
    vector<int> selfLoops;
    int vertexCount{};
    bool isDirected;
    bool init = false;
    int idCount = 0;

    explicit EulerianFinder(int vertexCount, bool directed) : vertexCount(vertexCount), graph(vertexCount), isDirected(directed) {
        inDegree.assign(vertexCount, 0);
        outDegree.assign(vertexCount, 0);
        selfLoops.assign(vertexCount, 0);
    }

    explicit EulerianFinder(vector<vector<int>> g, bool directed) : vertexCount(g.size()), isDirected(directed) {
        inDegree.assign(vertexCount, 0);
        outDegree.assign(vertexCount, 0);
        selfLoops.assign(vertexCount, 0);
        for (int from = 0; from < vertexCount; from++)
            for (int to : g[from])
                addEdge(from, to);
    }

    void addEdge(int from, int to, int weight = 1, int index = 0) {
        int id = idCount++;
        if (from == to) selfLoops[from]++;
        graph[from].emplace_back(from, to, weight, index);
        graph[from].back().id = id;
        outDegree[from]++;
        inDegree[to]++;
        if (!isDirected && from != to) {
            graph[to].emplace_back(to, from, weight, index);
            graph[to].back().id = id;
            outDegree[to]++;
            inDegree[from]++;
        }
    }


    bool hasEulerianCycle() {
        if (isDirected) {
            for (int u = 0; u < vertexCount; u++)
                if (outDegree[u] != inDegree[u])
                    return false;
        }
        else {
            for (int u = 0; u < vertexCount; u++)
                if ((graph[u].size() - selfLoops[u]) % 2 != 0)
                    return false;
        }
        return true;
    }

    bool hasEulerianPath() {
        if (isDirected) {
            int start = 0, end = 0;
            for (int u = 0; u < vertexCount; u++) {
                if (outDegree[u] - inDegree[u] == 1)
                    start++;
                else if (outDegree[u] - inDegree[u] == -1)
                    end++;
                else if (outDegree[u] != inDegree[u])
                    return false;
            }
            return (start + end == 0) || (start == 1 && end == 1);
        }
        int cnt = 0;
        for (int u = 0; u < vertexCount; u++)
            if ((graph[u].size() - selfLoops[u]) % 2 != 0)
                cnt++;
        return cnt == 0 || cnt == 2;
    }

    int findStartVertex() const {
        int start = 0;
        if (isDirected) {
            for (int u = 0; u < vertexCount; u++) {
                if (outDegree[u] - inDegree[u] == 1)
                    return u;
                if (outDegree[u] + inDegree[u] != 0)
                    start = u;
            }
        }
        else {
            for (int u = 0; u < vertexCount; u++) {
                if ((graph[u].size() - selfLoops[u]) % 2 != 0)
                    return u;
                if (!graph[u].empty())
                    start = u;
            }
        }
        return start;
    }
    void dfs(int u, vector<Edge>& path, vector<bool>& used, vector<int>& edgePtr) {
        while (edgePtr[u] < graph[u].size()) {
            int idx = edgePtr[u];
            const Edge& edge = graph[u][idx];
            if (used[edge.id]) {
                edgePtr[u]++;
                continue;
            }
            used[edge.id] = true;
            edgePtr[u]++;
            dfs(edge.to, path, used, edgePtr);
            path.push_back(edge);
        }
    }

    vector<Edge> findEulerianPath() {
        if (!hasEulerianPath())
            return {};
        int start = findStartVertex();
        vector<Edge> path;
        vector<bool> used(idCount, false);
        vector<int> edgePtr(vertexCount, 0);
        dfs(start, path, used, edgePtr);
        reverse(path.begin(), path.end());
        return path;
    }

    vector<Edge> findEulerianCycle() {
        if (!hasEulerianCycle())
            return {};
        return findEulerianPath();
    }
};