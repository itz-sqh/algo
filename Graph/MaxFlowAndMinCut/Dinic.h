#pragma once
#include <climits>
#include <queue>
#include <vector>
#include "Graph/Utils/Edge.h"

using namespace std;

struct Dinic {
    // Dinic
    // Time: O(n * m^2)
    // Space: O(n + m)
    vector<vector<Edge>> graph;
    vector<int> d, edgePtr;
    int vertexCount;

    explicit Dinic(int vertexCount) :
        graph(vertexCount), vertexCount(vertexCount), d(vertexCount, -1), edgePtr(vertexCount, 0) {}

    void addEdge(int from, int to, int capacity, int flow = 0) {
        int fromIndex = static_cast<int>(graph[from].size());
        int toIndex = static_cast<int>(graph[to].size());

        graph[from].emplace_back(from, to, capacity, flow);
        graph[to].emplace_back(to, from, 0, 0);

        graph[from][fromIndex].index = toIndex;
        graph[to][toIndex].index = fromIndex;
    }

    bool bfs(int start, int end) {
        fill(d.begin(), d.end(), -1);
        queue<int> q;
        d[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (const Edge& edge: graph[current]) {
                int to = edge.to;
                if (d[to] == -1 && edge.capacity - edge.flow > 0) {
                    d[to] = d[current] + 1;
                    q.push(to);
                }
            }
        }
        return d[end] != -1;
    }
    long long dfs(int start, int end, long long flow) {
        if (start == end)
            return flow;
        for (int& id = edgePtr[start]; id < static_cast<int>(graph[start].size()); ++id) {
            Edge& edge = graph[start][id];
            if (d[edge.to] != d[start] + 1)
                continue;
            long long avail = edge.capacity - edge.flow;
            if (avail <= 0)
                continue;
            long long pushed = dfs(edge.to, end, min(flow, avail));
            if (pushed > 0) {
                edge.flow += pushed;
                graph[edge.to][edge.index].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    long long findMaxFlow(int start, int end) {
        long long flow = 0;
        while (bfs(start, end)) {
            fill(edgePtr.begin(), edgePtr.end(), 0);
            while (long long pushed = dfs(start, end, LLONG_MAX))
                flow += pushed;
        }
        return flow;
    }
};
