#pragma once
#include "Graph/StronglyConnectedComponents/SCC.h"

struct SATSolver {
    // Solves 2-SAT problem using Kosaraju's algorithm for SCC
    // Time: O(n + m) where n is number of variables and m is number of clauses
    // Space: O(n + m)
    // 2 Sat https://judge.yosupo.jp/submission/311730
    int variableCount;
    SCC graph;

    explicit SATSolver(int variableCount) : variableCount(variableCount), graph(2 * variableCount) {}

    int getNode(int var, bool negated) const { return negated ? var + variableCount : var; }

    // One of them is true
    void addOr(int u, bool negateU, int v, bool negateV) {
        graph.addEdge(getNode(u, !negateU), getNode(v, negateV));
        graph.addEdge(getNode(v, !negateV), getNode(u, negateU));
    }
    // Only one of them is true
    void addXor(int u, bool negateU, int v, bool negateV) {
        addOr(u, negateU, v, negateV);
        addOr(u, !negateU, v, !negateV);
    }
    // Both of them have the same value
    void addAnd(int u, bool negateU, int v, bool negateV) { addXor(u, !negateU, v, negateV); }

    // First implies second
    void addImpl(int u, bool negateU, int v, bool negateV) { addOr(u, !negateU, v, negateV); }

    vector<int> solve() {
        graph.buildComponents();
        // Construct the answer
        vector<int> res(variableCount);
        for (int i = 0; i < variableCount; i++) {
            if (graph.comp[i] == graph.comp[i + variableCount])
                return {};
            res[i] = graph.comp[i] > graph.comp[i + variableCount];
        }
        return res;
    }
};
