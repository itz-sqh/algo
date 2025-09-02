#include "../../../Graph/ArticulationPointsAndBiconnectedComponents/APBC.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_A"

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
    auto res(bridgeFinder.articulationPoints);
    sort(begin(res), end(res));
    for (auto u: res) {
        cout << u << endl;
    }
}
