#pragma once
#include <climits>
#include <vector>
#include "Graph/Utils/Edge.h"

using namespace std;

struct FordFulkerson {
    // Ford-Fulkerson max flow algorithm using DFS
    // Time: O(m * f) where f is the max flow value
    // Space: O(n + m)
    vector<vector<Edge>> graph;
    vector<int> visited;
    int vertexCount;

    explicit FordFulkerson(int vertexCount) : graph(vertexCount), visited(vertexCount), vertexCount(vertexCount) {}

    void addEdge(int from, int to, int capacity, int flow = 0) {
        // store indices to reverse edges, can be done using pointers
        int fromIndex = graph[from].size();
        int toIndex = graph[to].size();

        graph[from].emplace_back(from, to, capacity, flow);
        graph[to].emplace_back(to, from, 0, flow);

        graph[from].back().index = toIndex;
        graph[to].back().index = fromIndex;
    }

    long long dfs(int start, int end, long long flow = LLONG_MAX) {
        if (start == end)
            return flow;
        if (visited[start])
            return 0;
        visited[start] = true;
        for (auto& edge: graph[start]) {
            if (edge.capacity - edge.flow > 0) {
                long long delta = dfs(edge.to, end, min(flow, 1ll * edge.capacity - edge.flow));
                if (delta > 0) {
                    edge.flow += delta;
                    graph[edge.to][edge.index].flow -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }
    long long findMaxFlow(int start, int end) {
        long long res = 0;
        while (true) {
            fill(visited.begin(), visited.end(), false);
            long long flow = dfs(start, end, LLONG_MAX);
            if (flow == 0)
                break;
            res += flow;
        }
        return res;
    }
};
