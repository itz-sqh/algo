#include "../../../Graph/BridgesAndTwo-EdgeConnectedComponents/B2ECC.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B"

int main() {
    // Bridges
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    B2ECC bridgeFinder(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        bridgeFinder.addEdge(u, v);
    }
    bridgeFinder.findBridgesAndComponents();
    vector<pair<int, int>> bridges;
    for (const auto& edge : bridgeFinder.bridges) {
        int u = edge.from;
        int v = edge.to;
        if (u > v) swap(u, v);
        bridges.emplace_back(u, v);
    }
    sort(bridges.begin(), bridges.end());
    for (auto& [u,v] : bridges) {
        cout << u << " " << v << "\n";
    }
    return 0;
}