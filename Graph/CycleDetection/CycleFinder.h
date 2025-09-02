#pragma once
#include <bits/stdc++.h>
#include "../Utils/Edge.h"

using namespace std;

struct CycleFinder {
    // Finds any cycle in both directed and undirected graphs
    // Time: O(n + m)
    // Space: O(n + m)
    // Cycle Detection (Undirected) : https://judge.yosupo.jp/submission/311519
    // Cycle Detection (Directed)   : https://judge.yosupo.jp/submission/311520
    vector<vector<Edge>> graph;
    vector<int> visited; // 0: not visited, 1: processing (in stack), 2: finished
    vector<int> cycle;
    vector<int> from;
    int vertexCount{};
    bool isDirected;

    explicit CycleFinder(int vertexCount, bool directed) : graph(vertexCount), vertexCount(vertexCount),
                                                           isDirected(directed) {
        vertexCount = graph.size();
        visited.assign(vertexCount, 0);
        from.assign(vertexCount, -1);
    }

    explicit CycleFinder(const vector<vector<int>>& g, bool directed) : vertexCount(g.size()), isDirected(directed) {
        visited.assign(vertexCount, 0);
        from.assign(vertexCount, -1);
        for (int _from = 0; _from < vertexCount; _from++)
            for (int to: g[_from])
                addEdge(_from, to);
    }

    void addEdge(int _from, int to, int weight = 1) {
        graph[_from].emplace_back(_from, to, weight);
        if (!isDirected)
            graph[to].emplace_back(to, _from, weight);
    }

    vector<int> getCycle(int lastVertex) {
        cycle.reserve(vertexCount);
        cycle.push_back(lastVertex);
        for (int i = from[lastVertex]; i != lastVertex; i = from[i])
            cycle.push_back(i);
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }

    bool dfs(int start, int parent = -1) {
        visited[start] = 1;
        int seenParent = 0;
        for (const Edge& edge: graph[start]) {
            int to = edge.to;
            if (!isDirected && to == parent) {
                if (seenParent) {
                    cycle = {parent, start};
                    return true;
                }
                seenParent++;
                continue;
            }
            if (visited[to] == 0) {
                from[to] = start;
                if (dfs(to, start))
                    return true;
            }
            else if (visited[to] == 1) {
                from[to] = start;
                cycle = getCycle(to);
                return true;
            }
        }
        visited[start] = 2;
        return false;
    }

    vector<int> findCycle() {
        for (int i = 0; i < vertexCount; i++)
            if (visited[i] == 0)
                if (dfs(i))
                    return cycle;
        return {};
    }
};
