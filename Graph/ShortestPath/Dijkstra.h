#pragma once
#include <vector>
#include <algorithm>
#include <queue>
#include "Edge.h"

using namespace std;

struct Dijkstra {
    // Finds shortest path in graphs without negative edges
    // Time: O((m + n) * log(n)) can be done in O(n^2) using array instead of heap
    // Space: O(m + n)
    int vertexCount;
    vector<vector<Edge>> graph;
    vector<long long> distance;
    vector<Edge> path;
    vector<Edge> from;
    bool isDirected;
    static constexpr long long INF = 1'000'000'000'000'000;

    explicit Dijkstra(int vertexCount, bool directed) :
        vertexCount(vertexCount), graph(vertexCount), distance(vertexCount, INF), from(vertexCount, {-1, -1, -1}),
        isDirected(directed) {}

    void addEdge(int from, int to, long long weight) {
        graph[from].emplace_back(from, to, weight);
        if (!isDirected)
            graph[to].emplace_back(to, from, weight);
    }

    vector<long long> findShortestPaths(int start) {
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        distance.assign(vertexCount, INF);
        from.assign(vertexCount, {-1, -1, -1});
        distance[start] = 0;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int current = pq.top().second;
            long long dist = pq.top().first;
            pq.pop();
            if (dist != distance[current])
                continue;
            for (const Edge& edge: graph[current]) {
                int to = edge.to;
                if (distance[current] + edge.weight < distance[to]) {
                    distance[to] = distance[current] + edge.weight;
                    from[to] = edge;
                    pq.emplace(distance[to], to);
                }
            }
        }
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
};
