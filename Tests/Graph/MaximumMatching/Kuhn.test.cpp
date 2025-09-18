#include <bits/stdc++.h>
#include "Graph/MaximumMatching/Kuhn.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/7/GRL_7_A"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    int x, y;
    cin >> x >> y >> m;
    n = x + y;
    Kuhn kuhn(n);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        v += x;
        kuhn.addEdge(u, v);
    }

    cout << kuhn.findMaxMatching() << endl;
}
