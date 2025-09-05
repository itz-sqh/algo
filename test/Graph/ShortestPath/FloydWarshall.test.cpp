#include "../../../Graph/ShortestPath/FloydWarshall.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_C"

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    FloydWarshall floyd(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        floyd.addEdge(u, v, w, true);
    }
    if (floyd.build()) {
        cout << "NEGATIVE CYCLE" << endl;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long d = floyd.getDistance(i, j);
            cout << (d == FloydWarshall::INF ? "INF" : to_string(d));
            if (j != n - 1)
                cout << " ";
        }
        cout << endl;
    }
}
