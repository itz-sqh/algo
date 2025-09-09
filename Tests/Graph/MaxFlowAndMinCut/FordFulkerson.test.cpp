#include "Graph/MaxFlowAndMinCut/FordFulkerson.h"
#include <bits/stdc++.h>
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    FordFulkerson ff(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ff.addEdge(u, v, w);
    }
    cout << ff.findMaxFlow(0, n-1) << endl;
}
