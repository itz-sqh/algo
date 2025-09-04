#pragma once

#include <bits/stdc++.h>
#include "../Utils/Edge.h"

using namespace std;

struct FordBellman {
    // Finds shortest path in graphs with negative edges and detects negative cycles
    // Time: O(n * m)
    // Space: O(m + n)
    int vertexCount;
    vector<vector<Edge>> graph;
    vector<int> distance;
    vector<Edge> path;
    vector<Edge> from;
    bool isDirected;
    bool hasNegativeCycle_;
    int lastUpdatedVertex;
    static constexpr long long INF = 1'000'000'000;

    explicit FordBellman(int vertexCount, bool directed) :
        vertexCount(vertexCount), graph(vertexCount), distance(vertexCount, INF), from(vertexCount, {-1, -1, -1}),
        isDirected(directed), hasNegativeCycle_(false), lastUpdatedVertex(-1) {}

    void addEdge(int from, int to, int weight) {
        graph[from].emplace_back(from, to, weight);
        if (!isDirected)
            graph[to].emplace_back(to, from, weight);
    }

    vector<int> findShortestPaths(int start) {
        hasNegativeCycle_ = false;
        lastUpdatedVertex = -1;
        distance.assign(vertexCount, INF);
        from.assign(vertexCount, {-1, -1, -1});
        distance[start] = 0;

        for (int k = 0; k < vertexCount; k++) {
            bool updated = false;
            for (int u = 0; u < vertexCount; u++) {
                if (distance[u] == INF)
                    continue;
                for (const Edge& edge: graph[u]) {
                    if (distance[edge.to] > distance[u] + edge.weight) {
                        distance[edge.to] = distance[u] + edge.weight;
                        from[edge.to] = edge;
                        updated = true;
                        lastUpdatedVertex = edge.to;
                        if (k == vertexCount - 1)
                            hasNegativeCycle_ = true;
                    }
                }
            }
            if (!updated)
                break;
        }
        if (hasNegativeCycle_)
            return {};
        return distance;
    }

    vector<Edge> getPath(int end) {
        path.clear();
        if (distance[end] == INF)
            return {};
        for (int current = end; from[current].from != -1; current = from[current].from)
            path.push_back(from[current]);
        reverse(path.begin(), path.end());
        return path;
    }

    bool hasNegativeCycle() const { return hasNegativeCycle_; }

    vector<Edge> findNegativeCycle() const {
        if (!hasNegativeCycle_ || lastUpdatedVertex == -1)
            return {};
        int curr = lastUpdatedVertex;
        for (int u = 0; u < vertexCount; u++)
            curr = from[curr].from;
        vector<Edge> cycle;
        for (int start = curr; curr != start; curr = from[curr].from)
            cycle.push_back(from[curr]);
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
};
