#pragma once
#include <bits/stdc++.h>
#include "../Utils/Edge.h"


using namespace std;

struct SATSolver {
    // Solves 2-SAT problem using Kosaraju's algorithm for SCC
    // Time: O(n + m) where n is number of variables and m is number of clauses
    // Space: O(n + m)
    // 2 Sat https://judge.yosupo.jp/submission/311730
    int variableCount;
    int vertexCount;
    vector<vector<Edge>> graph;
    vector<vector<Edge>> reversedGraph;
    vector<int> comp; // comp[v] - component index for vertex v
    vector<int> order;
    vector<int> visited;

    explicit SATSolver(int variableCount) : variableCount(variableCount), vertexCount(2 * variableCount),
                                            graph(vertexCount),
                                            reversedGraph(vertexCount), comp(vertexCount), visited(vertexCount, 0) {
        order.reserve(vertexCount);
    }

    int getNode(int var, bool negated) const {
        return negated ? var + variableCount : var;
    }

    void addEdge(int u, int v, int weight = 1) {
        graph[u].emplace_back(u, v, weight);
        reversedGraph[v].emplace_back(v, u, weight);
    }

    // One of them is true
    void addOr(int u, bool negateU, int v, bool negateV) {
        addEdge(getNode(u, !negateU), getNode(v, negateV));
        addEdge(getNode(v, !negateV), getNode(u, negateU));
    }

    // Only one of them is true
    void addXor(int u, bool negateU, int v, bool negateV) {
        addOr(u, negateU, v, negateV);
        addOr(u, !negateU, v, !negateV);
    }

    // Both of them have the same value
    void addAnd(int u, bool negateU, int v, bool negateV) {
        addXor(u, !negateU, v, negateV);
    }

    // First implies second
    void addImpl(int u, bool negateU, int v, bool negateV) {
        addOr(u, !negateU, v, negateV);
    }

    void dfs(int start) {
        visited[start] = true;
        for (Edge edge : graph[start])
            if (!visited[edge.to])
                dfs(edge.to);
        order.push_back(start);
    }

    void scc(int start, int id) {
        visited[start] = true;
        comp[start] = id;
        for (Edge edge : reversedGraph[start])
            if (!visited[edge.to])
                scc(edge.to, id);
    }

    vector<int> solve() {
        // Topological sort
        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        // Strongly connected components
        visited.assign(vertexCount, false);
        int id = 0;
        for (int i = vertexCount - 1; i >= 0; i--) {
            if (!visited[order[i]]) {
                scc(order[i], id++);
            }
        }
        // Construct the answer
        vector<int> res(variableCount);
        for (int i = 0; i < variableCount; i++) {
            if (comp[i] == comp[i + variableCount]) return {};
            res[i] = comp[i] > comp[i + variableCount];
        }
        return res;
    }
};