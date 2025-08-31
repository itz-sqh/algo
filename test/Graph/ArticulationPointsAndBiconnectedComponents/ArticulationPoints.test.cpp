#include "../../../Graph/ArticulationPointsAndBiconnectedComponents/APBC.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_A"

int main(){
    // Articulation Points
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
    auto res(bridgeFinder.articulationPoints);
    sort(begin(res), end(res));
    for (auto u : res){
        cout << u << endl;
    }
}
