#include "../../../Graph/LCA/LCA.h"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

int main(){
    int n, q;
    cin >> n >> q;
    vector<vector<int>> graph(n);
    for (int i = 1, p; i < n; i++){
        cin >> p;
        graph[p].push_back(i);
        graph[i].push_back(p);
    }
    LCA lca(graph, 0);
    while (q--){
        int u, v;
        cin >> u >> v;
        cout << lca.get(u, v) << endl;
    }
}
