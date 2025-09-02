#include "../../../Graph/StronglyConnectedComponents/SCC.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_C"

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
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << (scc.comp[u] == scc.comp[v]) << endl;
    }
}
