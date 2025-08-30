#include <bits/stdc++.h>

using namespace std;

struct SCC {
    // Finds strongly connected components in a directed graph using Kosaraju's algorithm
    // Time: O(n + m)
    // Space: O(n + m)
    // Strongly Connected Components https://judge.yosupo.jp/submission/311149
    vector<vector<int>> graph;
    vector<vector<int>> reversedGraph;
    vector<int> order;
    vector<int> visited;
    int vertexCount{};

    explicit SCC(const vector<vector<int>> &graph) : graph(graph) {
        vertexCount = graph.size();
        visited.assign(vertexCount, 0);

        reversedGraph.assign(vertexCount, vector<int>());
        for (int from = 0; from < vertexCount; from++)
            for (int to : graph[from])
                reversedGraph[to].push_back(from);
    }

    void dfs(int start) {
        visited[start] = true;
        for (int to : graph[start])
            if (!visited[to])
                dfs(to);
        order.push_back(start);
    }

    vector<vector<int>> buildComponents() {
        // Topological sort
        for (int i = 0; i < vertexCount; i++)
            if (!visited[i])
                dfs(i);

        vector<vector<int>> components;

        visited.assign(vertexCount, false);
        for (int i = order.size() - 1; i >= 0; i--) {
            if (!visited[order[i]]) {
                // Traverse the vertices in reverse topological order, through edges that point into the current vertex
                // One way to do that is using reversed graph
                auto dfs_comp = [&](auto&& dfs, int start) -> void {
                    visited[start] = true;
                    components.back().push_back(start);
                    for (int from : reversedGraph[start])
                        if (!visited[from])
                            dfs(dfs, from);
                };
                components.emplace_back();
                dfs_comp(dfs_comp, order[i]);
            }
        }
        return components;
    }


};

int main() {
    // Example usage
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    SCC scc(graph);

    auto components = scc.buildComponents();

    cout << components.size() << endl;

    for (auto &comp : components) {
        for (int vertex : comp) {
            cout << vertex << " ";
        }
        cout << endl;
    }


}