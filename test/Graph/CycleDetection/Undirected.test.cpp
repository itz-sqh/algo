#include "../../../Graph/CycleDetection/CycleFinder.h"
#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > graph(n);
    vector<pair<int, int> > edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        if (u != v) graph[v].push_back(u);
        edges.emplace_back(u, v);
    }

    CycleFinder finder(graph, false);
    vector<int> cycle = finder.findCycle();

    if (cycle.empty()) {
        cout << -1 << "\n";
        return 0;
    }

    int cycleSize = cycle.size();
    cout << cycleSize << "\n";
    for (int v: cycle) cout << v << " ";
    cout << endl;

    vector<vector<int> > edgeId(n);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        edgeId[u].push_back(i);
        if (u != v) edgeId[v].push_back(i);
    }

    vector<char> visited(m, 0);
    vector<int> cycleEdges;
    for (int i = 0; i < cycleSize; i++) {
        int u = cycle[i];
        int v = cycle[(i + 1) % cycleSize];
        int chosen = -1;
        for (int id: edgeId[u]) {
            if (visited[id]) continue;
            auto [a,b] = edges[id];
            if ((a == u && b == v) || (a == v && b == u)) {
                chosen = id;
                break;
            }
        }
        visited[chosen] = 1;
        cycleEdges.push_back(chosen);
    }

    for (int edge: cycleEdges) cout << edge << " ";
}