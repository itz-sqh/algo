#include "../../../Graph/CycleDetection/CycleFinder.h"
#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    CycleFinder finder(n, true);
    map<pair<int, int>, int> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        finder.addEdge(u, v);
        edges[{u, v}] = i;
    }

    vector<int> cycle = finder.findCycle();

    if (!cycle.empty()) {
        vector<int> edgeCycle;
        int cycleSize = cycle.size();

        for (int i = 0; i < cycleSize; i++) {
            int u = cycle[i];
            int v = cycle[(i + 1) % cycleSize];
            edgeCycle.push_back(edges[{u, v}]);
        }

        cout << edgeCycle.size() << endl;
        for (int edge: edgeCycle) {
            cout << edge << endl;
        }
    }
    else {
        cout << -1 << endl;
    }
}
