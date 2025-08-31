#include "../../../Graph/BridgesAndTwo-EdgeConnectedComponents/B2ECC.h"
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
int main(){
    // Find Two-Edge-Connected Components
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0, u, v; i < m; i++){
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    B2ECC componentsFinder(graph);
    componentsFinder.findBridgesAndComponents();
    cout << componentsFinder.twoEdgeConnectedComponents.size() << endl;
    for (auto& comp : componentsFinder.twoEdgeConnectedComponents){
        cout << comp.size() << " ";
        for (auto v : comp)
            cout << v << " ";
        cout << endl;
    }
}
