#include "EulerianFinder.h"
#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_directed"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        EulerianFinder finder(n, true);
        for (int i = 0, u, v, weight = 1; i < m; i++) {
            cin >> u >> v;
            finder.addEdge(u, v, weight, i);
        }

        auto path = finder.findEulerianPath();
        if (path.size() != m) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
        if (!path.empty()) {
            cout << path[0].from << " ";
            for (const Edge& edge: path)
                cout << edge.to << " ";
        }
        else {
            cout << "0" << endl;
        }
        cout << endl;
        for (const Edge& edge: path)
            cout << edge.index << " ";
        cout << endl;
    }
}
