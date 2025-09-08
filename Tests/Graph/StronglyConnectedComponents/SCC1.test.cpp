#include "Graph/StronglyConnectedComponents/SCC.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/scc"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    SCC scc(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        scc.addEdge(u, v);
    }
    auto components = scc.buildComponents();
    cout << components.size() << endl;
    for (auto& comp: components) {
        cout << comp.size() << " ";
        for (int v: comp) {
            cout << v << " ";
        }
        cout << endl;
    }
}
