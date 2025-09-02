#include "../../DSU/DSU.h"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    while (q--) {
        int op;
        cin >> op;
        int u, v;
        cin >> u >> v;
        if (op == 0) dsu.unionSet(u, v);
        else if (op == 1) cout << (dsu.findSet(u) == dsu.findSet(v) ? 1 : 0) << endl;
    }
}
