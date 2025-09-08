#include "LCAonSparseTable.h"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector graph(n, vector<int>());
    for (int i = 1, p; i < n; i++) {
        cin >> p;
        graph[p].push_back(i);
        graph[i].push_back(p);
    }
    LCAonSparseTable lca(graph, 0);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.get(u, v) << endl;
    }
}
