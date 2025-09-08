#pragma once
#include <vector>
#include <stack>
#include "Edge.h"

using namespace std;

struct B2ECC {
    // Find 2-edge connected components and bridges in undirected graph
    // Time: O(n + m)
    // Space: O(n + m)
    // Two-Edge-Connected Components : https://judge.yosupo.jp/submission/311338
    // Find bridges                  : https://codeforces.com/gym/100083/submission/336317416
    vector<vector<Edge>> graph;
    vector<int> visited;
    vector<int> tup;
    vector<int> tin;
    vector<Edge> bridges;
    vector<vector<int>> twoEdgeConnectedComponents;
    stack<int> buffer;
    int vertexCount;

    explicit B2ECC(int vertexCount) : graph(vertexCount), vertexCount(vertexCount) {
        visited.assign(vertexCount, 0);
        tup.resize(vertexCount);
        tin.resize(vertexCount);
    }

    explicit B2ECC(const vector<vector<int>>& g) : vertexCount(g.size()) {
        visited.assign(vertexCount, 0);
        tup.resize(vertexCount);
        tin.resize(vertexCount);
        for (int from = 0; from < vertexCount; from++)
            for (int to: g[from])
                addEdge(from, to);
    }

    void addEdge(int from, int to, int weight = 1) {
        graph[from].emplace_back(from, to, weight);
        graph[to].emplace_back(to, from, weight);
    }

    void dfs(int current, int parent = -1, int height = 0) {
        int seenParent = 0;
        visited[current] = 1;
        tin[current] = tup[current] = height;
        buffer.push(current);

        for (const Edge& edge: graph[current]) {
            int to = edge.to;
            if (to == parent) {
                seenParent++;
                continue;
            }
            if (!visited[to])
                dfs(to, current, height + 1);
            tup[current] = min(tup[current], tup[to]);
        }

        if (tup[current] == tin[current] && parent != -1 && seenParent == 1) {
            // find bridge, add new component
            Edge bridgeEdge(-1, -1, -1);
            for (const Edge& edge: graph[current])
                if (edge.to == parent)
                    bridgeEdge = edge;
            bridges.emplace_back(bridgeEdge);
            twoEdgeConnectedComponents.emplace_back();
            while (true) {
                int u = buffer.top();
                buffer.pop();
                twoEdgeConnectedComponents.back().emplace_back(u);
                if (u == current)
                    break;
            }
        }

        if (parent == -1 && !buffer.empty()) {
            // add component with parent
            twoEdgeConnectedComponents.emplace_back();
            while (!buffer.empty()) {
                int u = buffer.top();
                buffer.pop();
                twoEdgeConnectedComponents.back().emplace_back(u);
            }
        }
    }

    void findBridgesAndComponents() {
        for (int u = 0; u < vertexCount; u++) {
            if (!visited[u])
                dfs(u);
        }
    }
};
