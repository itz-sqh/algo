#include "../../../Graph/LCA/LCA.h"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"

int main(){
    int n, q;
    cin >> n;
    vector<vector<int>> graph(n);
    for (int i = 0, u, k; i < n; i++){
        cin >> k;
        while (k--){
            cin >> u;
            graph[u].push_back(i);
            graph[i].push_back(u);
        }
    }
    cin >> q;
    LCA lca(graph, 0);
    while (q--){
        int u, v;
        cin >> u >> v;
        cout << lca.get(u, v) << endl;
    }
}
