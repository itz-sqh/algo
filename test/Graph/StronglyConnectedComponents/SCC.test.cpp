#include "../../../Graph/StronglyConnectedComponents/SCC.h"
#define PROBLEM "https://judge.yosupo.jp/problem/scc"

int main(){
    //SCC
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    SCC scc(graph);

    auto component = scc.buildComponents();
    cout << component.size() << endl;
    for (auto& comp : component){
        cout << comp.size();
        for (int v : comp){
            cout << " " << v;
        }
        cout << endl;
    }
}
