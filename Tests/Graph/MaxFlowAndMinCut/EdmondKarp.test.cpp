#include "Graph/MaxFlowAndMinCut/EdmondsKapr.h"
#include <bits/stdc++.h>
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    EdmondsKarp ek(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ek.addEdge(u, v, w);
    }
    cout << ek.findMaxFlow(0, n-1) << endl;
}
