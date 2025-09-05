#pragma once
#include <bits/stdc++.h>
#include "../Utils/Edge.h"

using namespace std;

struct FloydWarshall {
    // Finds shortest path between any two vertices
    // Time: build() - O(n^3)
    // Space: O(n^2)
    int vertexCount;
    vector<vector<long long>> distance;
    static constexpr long long INF = 1'000'000'000'000'000;

    explicit FloydWarshall(int vertexCount) :
        vertexCount(vertexCount), distance(vertexCount, vector(vertexCount, INF)) {}

    void addEdge(int from, int to, long long weight, bool isDirected) {
        distance[from][to] = min(distance[from][to], weight);
        if (!isDirected)
            distance[to][from] = min(distance[to][from], weight);
    }

    void build() {
        for (int i = 0; i < vertexCount; i++)
            distance[i][i] = 0;
        for (int i = 0; i < vertexCount; i++)
            for (int j = 0; j < vertexCount; j++)
                for (int k = 0; k < vertexCount; k++)
                    if (distance[i][k] < INF && distance[k][j] < INF)
                        distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
    }

    long long getDistance(int from, int to) const {
        return distance[from][to];
    }
};
