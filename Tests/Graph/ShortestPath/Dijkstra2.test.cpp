#include "Dijkstra.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_A"
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    Dijkstra dijkstra(n, true);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dijkstra.addEdge(u, v, w);
    }
    vector<int> dist = dijkstra.findShortestPaths(s);
    for (auto d: dist) {
        if (d == Dijkstra::INF)
            cout << "INF" << endl;
        else
            cout << d << endl;
    }
}
