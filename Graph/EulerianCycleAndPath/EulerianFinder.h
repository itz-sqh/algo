#pragma once
#include <bits/stdc++.h>
#include "../Utils/Edge.h"

using namespace std;


struct EulerianFinder {
    // Check for and find Eulerian paths and cycles in directed or undirected graphs with self-loops and parallel edges
    // Time : check - O(n), find - O(m)   without copy graph [O(n+m)]
    // Space: check - O(1), find - O(n+m) without copy graph [O(n+m)]
    vector<vector<Edge>> mainGraph;
    vector<int> inDegree, outDegree;
    vector<int> selfLoops;
    int vertexCount{};
    bool isDirected;
    bool init = false;
    int idCount = 0;

    EulerianFinder(int vertexCount, bool directed) : vertexCount(vertexCount), mainGraph(vertexCount), isDirected(directed) {
        inDegree.assign(vertexCount, 0);
        outDegree.assign(vertexCount, 0);
        selfLoops.assign(vertexCount, 0);
    }


    void addEdge(int from, int to, int weight = 1, int index = 0) {
        int id = idCount++;
        if (from == to) {
            selfLoops[from]++;
            mainGraph[from].emplace_back(from, to, weight, index);
            mainGraph[from].back().id = id;
        }
        else {
            mainGraph[from].emplace_back(from, to, weight, index);
            mainGraph[from].back().id = id;

            if (!isDirected) {
                mainGraph[to].emplace_back(to, from, weight, index);
                mainGraph[to].back().id = id;
            }
        }
        outDegree[from]++;
        inDegree[to]++;
        if (!isDirected && from != to) {
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
                if ((mainGraph[u].size() - selfLoops[u]) % 2 != 0)
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
            if ((mainGraph[u].size() - selfLoops[u]) % 2 != 0)
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
                if ((mainGraph[u].size() - selfLoops[u]) % 2 != 0)
                    return u;
                if (!mainGraph[u].empty())
                    start = u;
            }
        }
        return start;
    }
    void dfs(int u, vector<Edge>& path, vector<bool>& used, vector<int>& edgePtr) {
        while (edgePtr[u] < mainGraph[u].size()) {
            int idx = edgePtr[u];
            Edge edge = mainGraph[u][idx];
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