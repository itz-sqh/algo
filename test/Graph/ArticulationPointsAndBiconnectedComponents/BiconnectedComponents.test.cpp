#include "../../../Graph/ArticulationPointsAndBiconnectedComponents/APBC.h"
#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

int main(){
    // Biconnected Components
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0, u, v; i < m; i++){
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    APBC bridgeFinder(graph);
    bridgeFinder.findPointsAndComponents();
    cout << bridgeFinder.biconnectedComponents.size() << endl;
    for (auto& comp : bridgeFinder.biconnectedComponents){
        cout << comp.size() << " ";
        for (auto v : comp)
            cout << v << " ";
        cout << endl;
    }
}
