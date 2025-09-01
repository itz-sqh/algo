#include "../../../Graph/EulerianCycleAndPath/EulerianFinder.h"
#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_undirected"
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        EulerianFinder finder(n, false);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            finder.addEdge(u, v, 1, i);
        }

        auto path = finder.findEulerianPath();

        if (path.size() != m) {
            cout << "No" << endl;
            continue;
        }

        cout << "Yes" << endl;

        if (!path.empty()) {
            cout << path[0].from << " ";
            for (const Edge& edge : path) {
                cout << edge.to << " ";
            }
        }
        cout << endl;

        for (const Edge& edge : path) {
            cout << edge.index << " ";
        }
        cout << endl;
    }
    return 0;
}
