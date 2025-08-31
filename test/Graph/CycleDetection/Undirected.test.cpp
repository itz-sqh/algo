#include "../../../Graph/CycleDetection/CycleFinder.h"
#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"
int main(){
    // Undirected
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    map<pair<int, int>, int> edges;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges[{u, v}] = i;
        edges[{v, u}] = i;
    }
    CycleFinder finder(graph, false);
    vector<int> cycle = finder.findCycle();

    if (!cycle.empty()){
        vector<int> cycleEdges;
        int cycleSize = cycle.size();

        for (int i = 0; i < cycleSize; i++){
            int u = cycle[i];
            int v = cycle[(i + 1) % cycleSize];
            cycleEdges.push_back(edges[{u, v}]);
        }

        cout << cycleSize << endl;

        for (int i = 0; i < cycleSize; i++){
            cout << cycle[i];
            if (i < cycleSize - 1) cout << " ";
        }
        cout << endl;

        for (int i = 0; i < cycleSize; i++){
            cout << cycleEdges[i];
            if (i < cycleSize - 1) cout << " ";
        }
        cout << endl;
    }
    else{
        cout << -1 << endl;
    }
}
