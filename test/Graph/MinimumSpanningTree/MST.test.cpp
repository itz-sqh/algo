#include "../../../Graph/MinimumSpanningTree/MST.h"
#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    MST mst(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        mst.addAdge(u, v, w, i);
    }
    vector<Edge> edges = mst.buildMST();
    long long res = 0;
    for (auto &edge: edges) {
        res += edge.weight;
    }
    cout << res << endl;
    for (auto &edge: edges) {
        cout << edge.index << " ";
    }
}
