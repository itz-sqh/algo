#include "../../../Graph/CycleDetection/CycleFinder.h"
#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

int main(){
    // Directed
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    map<pair<int, int>, int> edges;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        edges[{u, v}] = i;
    }
    CycleFinder finder(graph, true);
    vector<int> cycle = finder.findCycle();

    if (!cycle.empty()){
        vector<int> edgeCycle;
        int cycleSize = cycle.size();

        for (int i = 0; i < cycleSize; i++){
            int u = cycle[i];
            int v = cycle[(i + 1) % cycleSize];
            edgeCycle.push_back(edges[{u, v}]);
        }

        cout << edgeCycle.size() << "\n";
        for (int edge : edgeCycle){
            cout << edge << "\n";
        }
    }
    else{
        cout << "-1\n";
    }
}
