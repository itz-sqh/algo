#include "LCA.h"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    LCA lca(n, 0);
    for (int i = 1, p; i < n; i++) {
        cin >> p;
        lca.addEdge(p, i);
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.get(u, v) << endl;
    }
}
