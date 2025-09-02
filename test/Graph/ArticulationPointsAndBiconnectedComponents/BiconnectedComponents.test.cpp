#include "../../../Graph/ArticulationPointsAndBiconnectedComponents/APBC.h"
#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    APBC bridgeFinder(n);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        bridgeFinder.addEdge(u, v);
    }

    bridgeFinder.findPointsAndComponents();
    cout << bridgeFinder.biconnectedComponents.size() << endl;
    for (auto& comp: bridgeFinder.biconnectedComponents) {
        cout << comp.size() << " ";
        for (auto v: comp)
            cout << v << " ";
        cout << endl;
    }
}
