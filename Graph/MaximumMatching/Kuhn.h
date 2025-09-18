#pragma once
#include <vector>
#include "Graph/Utils/Edge.h"

using namespace std;

struct Kuhn {
    // Find biconnected components and articulation points in undirected graph
    // Time: O(n*m)
    // Space: O(n + m)
    vector<vector<Edge>> graph;
    int vertexCount;
    vector<int> matching;
    vector<bool> visited;

    explicit Kuhn(int vertexCount) :
        graph(vertexCount), vertexCount(vertexCount), matching(vertexCount, -1), visited(vertexCount, false) {}

    explicit Kuhn(const vector<vector<int>>& g) :
        graph(g.size()), vertexCount(g.size()), matching(g.size(), -1), visited(g.size(), false) {
        for (int from = 0; from < vertexCount; from++) {
            for (const auto to: g[from]) {
                graph[from].emplace_back(from, to);
                graph[to].emplace_back(to, from);
            }
        }
    }

    void addEdge(int from, int to) {
        graph[from].emplace_back(from, to);
        graph[to].emplace_back(to, from);
    }

    bool dfs(int current) {
        if (visited[current])
            return false;
        visited[current] = true;
        for (const auto& e: graph[current]) {
            if (matching[e.to] == -1 || dfs(matching[e.to])) {
                matching[e.to] = current;
                matching[current] = e.to;
                return true;
            }
        }
        return false;
    }

    int findMaxMatching() {
        int result = 0;

        for (int u = 0; u < vertexCount; u++) {
            if (matching[u] == -1) {
                fill(visited.begin(), visited.end(), false);
                if (dfs(u))
                    result++;
            }
        }

        return result;
    }

};
