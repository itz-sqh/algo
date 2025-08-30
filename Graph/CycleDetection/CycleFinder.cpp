#include <bits/stdc++.h>

using namespace std;

struct CycleFinder {
    // Finds any cycle in both directed and undirected graphs
    // Graph should not contain self-loops or multiple edges
    // Time: O(n + m)
    // Space: O(n + m)
    // Cycle Detection (Directed) https://judge.yosupo.jp/submission/311123
    // Cycle Detection (Undirected) https://judge.yosupo.jp/submission/311124
    vector<vector<int>> graph;
    vector<int> visited; // 0: not visited, 1: processing (in stack), 2: finished
    vector<int> cycle;
    vector<int> from;
    int vertexCount{};
    bool isDirected;

    CycleFinder(const vector<vector<int> >& graph, bool directed) : graph(graph), isDirected(directed) {
        vertexCount = graph.size();
        visited.assign(vertexCount, 0);
        from.assign(vertexCount, -1);
    }

    vector<int> getCycle(const vector<int> &from, int lastVertex) {
        cycle.reserve(vertexCount);
        cycle.push_back(lastVertex);
        for (int i = from[lastVertex]; i != lastVertex; i = from[i])
            cycle.push_back(i);
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }

    bool dfs(int start, int parent = -1) {
        visited[start] = 1;

        for (int to: graph[start]) {
            if (!isDirected && to == parent) continue;

            if (visited[to] == 0) {
                from[to] = start;
                if (dfs(to, start))
                    return true;
            }
            else if (visited[to] == 1) {
                from[to] = start;
                cycle = getCycle(from, to);
                return true;
            }
        }
        visited[start] = 2;
        return false;
    }

    vector<int> findCycle() {
        for (int i = 0; i < vertexCount; i++)
            if (visited[i] == 0)
                if (dfs(i))
                    return cycle;
        return {};
    }
};


int main() {
    // Example usage
    int n, m;
    cin >> n >> m;


    vector<vector<int> > graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
    }

    CycleFinder finder(graph, true);

    auto cycle = finder.findCycle();

    for (auto x : cycle)
        cout << x + 1 << " ";

}