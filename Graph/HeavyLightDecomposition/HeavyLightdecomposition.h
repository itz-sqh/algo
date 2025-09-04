#pragma once
#include <bits/stdc++.h>
#include "../Utils/LCAonSparseTable.h"
#include  "../Utils/SumSegmentTree.h"

using namespace std;

struct HeavyLight {
    //
    // Time :
    // Space :
    vector<vector<int>> graph;
    vector<long long> val;
    int root;
    int n;
    vector<int> parent;
    vector<int> head;
    vector<int> pos;
    int curPos;
    vector<int> heavyTo;
    vector<int> depth;
    LcAonSparseTable lca;
    SumSegmentTree tree;

    HeavyLight(const vector<vector<int>>& graph, const vector<long long>& a, int root) :
        graph(graph), val(graph.size()), root(root), n(graph.size()), lca(graph, root), tree(graph.size()) {
        build();
        for (int i = 0; i < n; i++)
            val[pos[i]] = a[i];
        tree.init(val);
    }

    void build() {
        parent.assign(n, 0);
        head.assign(n, 0);
        pos.assign(n, 0);
        curPos = 0;
        heavyTo.assign(n, -1);
        depth.assign(n, 0);
        dfs(root, root, 0);
        decompose(root, root);
    }

    int dfs(int current, int p, int d) {
        parent[current] = p;
        depth[current] = d;
        int size = 1;
        int maxSubTreeSize = 0;
        for (int to: graph[current]) {
            if (to == p)
                continue;
            int subTreeSize = dfs(to, current, d + 1);
            if (subTreeSize > maxSubTreeSize) {
                heavyTo[current] = to;
                maxSubTreeSize = subTreeSize;
            }
            size += subTreeSize;
        }
        return size;
    }

    void decompose(int current, int h) {
        head[current] = h;
        pos[current] = curPos++;
        if (heavyTo[current] != -1)
            decompose(heavyTo[current], h);
        for (int to: graph[current])
            if (to != parent[current] && heavyTo[current] != to)
                decompose(to, to);
    }

    void update(int u, long long value) {
        tree.update(pos[u], value);
    }

    long long query(int u, int v) {
        int anc = lca.get(u, v);
        return query_path(u, anc) + query_path(v, anc) - tree.query(pos[anc], pos[anc] + 1);
    }

    long long query_path(int u, int v) {
        long long res = 0;
        if (depth[head[u]] < depth[head[v]])
            swap(u, v);
        while (head[u] != head[v]) {
            res += tree.query(pos[head[u]], pos[u] + 1);
            u = parent[head[u]];
        }
        res += tree.query(min(pos[u], pos[v]), max(pos[u], pos[v]) + 1);
        return res;
    }
};
