#include "Graph/ShortestPath/Dijkstra.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dijkstra dijkstra(n, true);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dijkstra.addEdge(u, v, w);
    }
    vector<long long> dist = dijkstra.findShortestPaths(s);
    vector<Edge> path = dijkstra.getPath(t);

    if (path.empty()) {
        cout << -1 << endl;
        return 0;
    }
    cout << dist[t] << " " << path.size() << endl;

    for (const Edge& edge: path)
        cout << edge.from << " " << edge.to << endl;
}
