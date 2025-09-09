#pragma once
#include <vector>
#include <unordered_set>
#include "Graph/Utils/Edge.h"
using namespace std;

struct SCC {
    // Finds strongly connected components in a directed graph using Kosaraju's algorithm
    // Time: O(n + m)
    // Space: O(n + m)
    // Strongly Connected Components https://judge.yosupo.jp/submission/311727
    vector<vector<Edge>> graph;
    vector<vector<Edge>> reversedGraph;
    vector<int> comp; // comp[v] - component index for vertex v
    vector<vector<int>> components;
    int vertexCount{};

    explicit SCC(int vertexCount) : vertexCount(vertexCount) {
        graph.resize(vertexCount);
        reversedGraph.resize(vertexCount);
        comp.resize(vertexCount);
        components.reserve(vertexCount);
    }

    void addEdge(int from, int to, int weight = 1) {
        graph[from].emplace_back(from, to, weight);
        reversedGraph[to].emplace_back(to, from, weight);
    }

    vector<vector<int>> buildComponents() {
        vector<int> order(vertexCount);
        vector<int> visited(vertexCount, false);
        auto topologicalSort = [&](auto&& topSort, int start = 0) -> void {
            visited[start] = true;
            for (const Edge& edge: graph[start])
                if (!visited[edge.to])
                    topSort(topSort, edge.to);
            order.push_back(start);
        };
        for (int i = 0; i < vertexCount; i++)
            if (!visited[i])
                topologicalSort(topologicalSort, i);

        visited.assign(vertexCount, false);
        comp.assign(vertexCount, -1);
        int compId = 0;
        for (int i = order.size() - 1; i >= 0; i--) {
            if (!visited[order[i]]) {
                // Traverse the vertices in reverse topological order, through edges that point into the current vertex
                // One way to do that is using reversed graph
                auto dfsRev = [&](auto&& dfs, int start) -> void {
                    visited[start] = true;
                    comp[start] = compId;
                    components.back().push_back(start);
                    for (const Edge& edge: reversedGraph[start])
                        if (!visited[edge.to])
                            dfs(dfs, edge.to);
                };
                components.emplace_back();
                dfsRev(dfsRev, order[i]);
                compId++;
            }
        }
        return components;
    }

    vector<vector<Edge>> condense() {
        if (components.empty())
            buildComponents();
        int componentCount = components.size();
        vector<vector<Edge>> condensedGraph(componentCount);
        vector<unordered_set<int>> usedEdges(componentCount);
        for (int from = 0; from < vertexCount; from++) {
            for (const Edge& edge: graph[from]) {
                int to = edge.to;
                if (comp[from] != comp[to] && !usedEdges[comp[from]].count(comp[to])) {
                    condensedGraph[comp[from]].emplace_back(comp[from], comp[to], edge.weight);
                    usedEdges[comp[from]].insert(comp[to]);
                }
            }
        }
        return condensedGraph;
    }
};
