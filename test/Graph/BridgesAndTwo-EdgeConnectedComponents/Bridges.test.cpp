#include "../../../Graph/BridgesAndTwo-EdgeConnectedComponents/B2ECC.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B"

int main(){
    // Bridges
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
    auto res(componentsFinder.bridges);
    for (auto& [u,v] : res)
        if (u > v)
            swap(u, v);
    sort(res.begin(), res.end());
    for (auto [u,v] : res){
        cout << u << " " << v << endl;
    }
}
