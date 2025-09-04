#include "../../../Graph/HeavyLightDecomposition/HeavyLightdecomposition.h"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<vector<int>> graph(n);
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    HeavyLight decomposition(graph, a, 0);

    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int p, x;
            cin >> p >> x;
            a[p] += x;
            decomposition.update(p, a[p]);
        }
        else if (op == 1) {
            int u, v;
            cin >> u >> v;
            cout << decomposition.query(u, v) << endl;
        }
    }
}
