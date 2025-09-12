#include "Graph/MaxFlowAndMinCut/Dinic.h"
#include <bits/stdc++.h>
using namespace std;
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Dinic dinic(n);
    for (int i = 0; i < m; i++) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        dinic.addEdge(from, to, capacity);
    }
    cout << dinic.findMaxFlow(0, n - 1) << endl;
}
