#include <bits/stdc++.h>

using namespace std;

struct APBC{
    // Find biconnected components and articulation points in undirected graph
    // Time: O(n + m)
    // Space: O(n + m)
    // Biconnected Components   : https://judge.yosupo.jp/submission/311414
    // Find articulation points : https://codeforces.com/gym/100083/submission/336345473
    vector<vector<int>> graph;
    vector<int> visited;
    vector<int> t_up;
    vector<int> t_in;
    vector<int> isArticulationPoint;
    vector<int> articulationPoints;
    vector<vector<int>> biconnectedComponents;
    stack<int> buffer;
    int vertexCount;

    explicit APBC(const vector<vector<int>>& graph) : graph(graph), vertexCount(graph.size()){
        visited.assign(vertexCount, 0);
        isArticulationPoint.assign(vertexCount, 0);
        t_up.resize(vertexCount);
        t_in.resize(vertexCount);
    }

    void dfs(int current, int parent = -1, int height = 0){
        visited[current] = 1;
        int children = 0;
        t_in[current] = t_up[current] = height;
        buffer.push(current);
        for (int to : graph[current]){
            if (to == parent) continue;
            if (!visited[to]){
                children++;
                dfs(to, current, height + 1);
                t_up[current] = min(t_up[current], t_up[to]);
                if ((t_up[to] >= t_in[current] && parent != -1) || (parent == -1 && children > 1)){
                    isArticulationPoint[current] = 1;
                    extractComponent(to, current);
                }
            }
            else{
                t_up[current] = min(t_up[current], t_in[to]);
            }
        }
        if (parent == -1)
            extractComponent(current, -1);
    }

    void extractComponent(int subTreeRoot, int current){
        biconnectedComponents.emplace_back();
        vector<int>& comp = biconnectedComponents.back();
        if (current != -1)
            comp.push_back(current);
        while (true){
            int x = buffer.top();
            buffer.pop();
            comp.push_back(x);
            if (x == subTreeRoot) return;
        }
    }

    void findPointsAndComponents(){
        for (int u = 0; u < vertexCount; u++){
            if (!visited[u]){
                dfs(u);
            }
        }
        for (int i = 0; i < vertexCount; i++)
            if (isArticulationPoint[i])
                articulationPoints.push_back(i);
    }
};


int main(){
    // Example usage
    /* Biconnected Components
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
    */
    /* Find articulation points
    ifstream cin("points.in");
    ofstream cout("points.out");
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0, u, v; i < m; i++){
        cin >> u >> v;
        u--;
        v--;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    APBC bridgeFinder(graph);
    bridgeFinder.findPointsAndComponents();
    set<int> res;
    for (auto v : bridgeFinder.articulationPoints)
        res.insert(v);
    cout << res.size() << endl;
    for (auto i : res)
        cout << i + 1 << endl;
    */
}
