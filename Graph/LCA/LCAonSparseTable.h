#pragma once
#include <vector>
#include "SparseTable/SparceTable.h"

using namespace std;

struct LCAonSparseTable {
    // LCA with Sparse Table
    // Time  : Preprocessing - O(n * log(n)), Query - O(log n)
    // Space : O(n * log(n))
    vector<vector<int>> graph;
    vector<int> eulerPass;
    vector<int> pos;
    vector<int> ind;
    vector<int> vert;
    int n;
    int root;
    int index;
    SparseTable table;

    LCAonSparseTable(const vector<vector<int>>& graph, int root) :
        graph(graph), pos(graph.size(), -1), ind(graph.size()), vert(graph.size()), n(graph.size()), root(root) {
        build();
        table = SparseTable(eulerPass);
    }

    void build() {
        index = 0;
        dfs(root, -1);
    }

    void dfs(int current, int parent) {
        ind[current] = index++;
        vert[ind[current]] = current;
        pos[current] = eulerPass.size();
        eulerPass.push_back(ind[current]);
        for (int to: graph[current]) {
            if (to == parent)
                continue;
            dfs(to, current);
            eulerPass.push_back(ind[current]);
        }
    }

    int get(int u, int v) const {
        int l = pos[u], r = pos[v];
        if (l > r)
            swap(l, r);
        return vert[table.getMin(l, r + 1)];
    }
};
