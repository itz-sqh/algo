#pragma once
#include <climits>
#include <queue>
#include <vector>
#include "Graph/Utils/Edge.h"

using namespace std;

struct EdmondsKarp {
    // Edmonds-Karp max flow algorithm using BFS
    // Time: O(n * m^2)
    // Space: O(n + m)
    vector<vector<Edge>> graph;
    vector<int> visited;
    vector<Edge*> from;
    int vertexCount;

    explicit EdmondsKarp(int vertexCount) : graph(vertexCount), visited(vertexCount), from(vertexCount), vertexCount(vertexCount) {}

    void addEdge(int from, int to, int capacity, int flow = 0) {
        // store indices to reverse edges, can be done using pointers
        int fromIndex = graph[from].size();
        int toIndex = graph[to].size();

        graph[from].emplace_back(from, to, capacity, flow);
        graph[to].emplace_back(to, from, 0, flow);

        graph[from].back().index = toIndex;
        graph[to].back().index = fromIndex;
    }

    long long bfs(int start, int end) {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            if (current == end) {
                long long flow = LLONG_MAX;
                int u = end;
                while (u != start) {
                    flow = min(flow, 1ll * from[u]->capacity - from[u]->flow);
                    u = from[u]->from;
                }
                u = end;
                while (u != start) {
                    from[u]->flow += flow;
                    graph[u][from[u]->index].flow -= flow;
                    u = from[u]->from;
                }
                return flow;
            }
            for (auto& edge: graph[current]) {
                int to = edge.to;
                if (!visited[to] && edge.capacity - edge.flow > 0) {
                    visited[to] = true;
                    from[to] = &edge;
                    q.push(to);
                }
            }
        }
        return 0;
    }
    long long findMaxFlow(int start, int end) {
        long long res = 0;
        while (true) {
            fill(visited.begin(), visited.end(), false);
            long long flow = bfs(start, end);
            if (flow == 0)
                break;
            res += flow;
        }
        return res;
    }
};