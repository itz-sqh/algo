#include <bits/stdc++.h>

using namespace std;

struct B2ECC{
    // Find 2-edge connected components and bridges in undirected graph
    // Time: O(n + m)
    // Space: O(n + m)
    // Two-Edge-Connected Components : https://judge.yosupo.jp/submission/311338
    // Find bridges                  : https://codeforces.com/gym/100083/submission/336317416
    vector<vector<int>> graph;
    vector<int> visited;
    vector<int> t_up;
    vector<int> t_in;
    vector<pair<int, int>> bridges;
    vector<vector<int>> twoEdgeConnectedComponents;
    stack<int> buffer;
    int vertexCount;

    explicit B2ECC(const vector<vector<int>>& graph) : graph(graph), vertexCount(graph.size()){
        visited.assign(vertexCount, 0);
        t_up.resize(vertexCount);
        t_in.resize(vertexCount);
    }

    void dfs(int current, int parent = -1, int height = 0){
        int seenParent = 0;
        visited[current] = 1;
        t_in[current] = t_up[current] = height;
        buffer.push(current);
        for (int to : graph[current]){
            if (to == parent){
                seenParent++;
                continue;
            }
            if (!visited[to])
                dfs(to, current, height + 1);
            t_up[current] = min(t_up[current], t_up[to]);
        }
        if (t_up[current] == t_in[current] && parent != -1 && seenParent == 1){
            // find bridge, add new component
            bridges.emplace_back(current, parent);
            twoEdgeConnectedComponents.emplace_back();
            while (true){
                int u = buffer.top();
                buffer.pop();
                twoEdgeConnectedComponents.back().emplace_back(u);
                if (u == current)
                    break;
            }
        }
        if (parent == -1 && !buffer.empty()){
            //add component with parent
            twoEdgeConnectedComponents.emplace_back();
            while (!buffer.empty()){
                int u = buffer.top();
                buffer.pop();
                twoEdgeConnectedComponents.back().emplace_back(u);
            }
        }
    }

    void findBridgesAndComponents(){
        for (int u = 0; u < vertexCount; u++){
            if (!visited[u])
                dfs(u);
        }
    }
};


int main(){
    // Example usage
    /* Find Two-Edge-Connected Components
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0, u, v; i < m; i++){
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    B2ECC bridgeFinder(graph);
    bridgeFinder.findBridgesAndComponents();
    cout << bridgeFinder.TwoEdgeConnectedComponents.size() << endl;
    for (auto& comp : bridgeFinder.TwoEdgeConnectedComponents){
        cout << comp.size() << " ";
        for (auto v : comp)
            cout << v << " ";
        cout << endl;
    }
    */
    /*Find bridges
    ifstream cin("bridges.in");
    ofstream cout("bridges.out");
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    map<pair<int, int>, int> edgesIndexes;
    for (int i = 0, u, v; i < m; i++){
        cin >> u >> v;
        u--;
        v--;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
        edgesIndexes[{u, v}] = i + 1;
        edgesIndexes[{v, u}] = i + 1;
    }
    B2ECC bridgeFinder(graph);
    bridgeFinder.findBridgesAndComponents();
    set<int> res;
    for (auto [u,v] : bridgeFinder.bridges)
        res.insert(edgesIndexes[{u, v}]);
    cout << res.size() << endl;
    for (auto i : res)
        cout << i << " ";
    */
}
