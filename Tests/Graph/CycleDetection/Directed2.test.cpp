#include "Graph/CycleDetection/CycleFinder.h"
#include <bits/stdc++.h>
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_4_A"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    CycleFinder finder(n, true);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        finder.addEdge(u, v);
    }
    vector<int> cycle = finder.findCycle();
    cout << 1 - cycle.empty() << endl;
}
