#include "../../../Graph/EulerianCycleAndPath/EulerianFinder.h"
#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_undirected"

int main(){
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        map<pair<int, int>, stack<int>> edges;
        vector<vector<int>> graph(n);
        for (int i = 0, u, v; i < m; i++){
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
            edges[{min(u, v), max(u, v)}].push(i);
        }
        EulerianFinder finder(graph, false);
        auto path = finder.findEulerianPath();
        if (path.size() - 1 != m){
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
        for (int u : path)
            cout << u << " ";
        cout << endl;
        for (int i = 0; i < path.size() - 1; i++){
            int u = path[i];
            int v = path[i + 1];
            cout << edges[{min(u, v), max(u, v)}].top() << " ";
            edges[{min(u, v), max(u, v)}].pop();
        }
        cout << endl;
    }
}
