#include "../../../Graph/ShortestPath/FordBellman.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_B"
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    FordBellman fordBellman(n, true);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        fordBellman.addEdge(u, v, w);
    }
    vector<int> dist = fordBellman.findShortestPaths(s);
    if (fordBellman.hasNegativeCycle()) {
        cout << "NEGATIVE CYCLE" << endl;
        return 0;
    }
    for (auto d: dist) {
        if (d == FordBellman::INF)
            cout << "INF" << endl;
        else
            cout << d << endl;
    }
}
