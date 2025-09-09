#include "Graph/LCA/LCA.h"
#include <bits/stdc++.h>
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n;
    LCA lca(n, 0);
    for (int i = 0, u, k; i < n; i++) {
        cin >> k;
        while (k--) {
            cin >> u;
            lca.addEdge(u, i);
        }
    }
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.get(u, v) << endl;
    }
}
