#include "Graph/BridgesAndTwo-EdgeConnectedComponents/B2ECC.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    B2ECC componentsFinder(n);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        componentsFinder.addEdge(u, v);
    }
    componentsFinder.findBridgesAndComponents();
    cout << componentsFinder.twoEdgeConnectedComponents.size() << endl;
    for (auto& comp: componentsFinder.twoEdgeConnectedComponents) {
        cout << comp.size() << " ";
        for (auto v: comp)
            cout << v << " ";
        cout << endl;
    }
}
