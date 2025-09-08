#pragma once
#include <vector>
#include <stack>
#include "Edge.h"

using namespace std;

struct APBC {
    // Find biconnected components and articulation points in undirected graph
    // Time: O(n + m)
    // Space: O(n + m)
    // Biconnected Components   : https://judge.yosupo.jp/submission/311414
    // Find articulation points : https://codeforces.com/gym/100083/submission/336345473
    vector<vector<Edge>> graph;
    vector<int> visited;
    vector<int> tup;
    vector<int> tin;
    vector<int> isArticulationPoint;
    vector<int> articulationPoints;
    vector<vector<int>> biconnectedComponents;
    stack<int> buffer;
    int vertexCount;

    explicit APBC(int vertexCount) : graph(vertexCount), vertexCount(vertexCount) {
        visited.resize(vertexCount, 0);
        isArticulationPoint.resize(vertexCount, 0);
        tup.resize(vertexCount);
        tin.resize(vertexCount);
    }

    explicit APBC(const vector<vector<int>>& g) : vertexCount(g.size()) {
        visited.resize(vertexCount, 0);
        isArticulationPoint.resize(vertexCount, 0);
        tup.resize(vertexCount);
        tin.resize(vertexCount, 0);
        for (int from = 0; from < vertexCount; from++)
            for (int to: g[from])
                addEdge(from, to);
    }

    void addEdge(int from, int to, int weight = 1) {
        graph[from].emplace_back(from, to, weight);
        graph[to].emplace_back(to, from, weight);
    }

    void dfs(int current, int parent = -1, int height = 0) {
        visited[current] = 1;
        int children = 0;
        tin[current] = tup[current] = height;
        buffer.push(current);
        for (const Edge& edge: graph[current]) {
            int to = edge.to;
            if (to == parent)
                continue;
            if (!visited[to]) {
                children++;
                dfs(to, current, height + 1);
                tup[current] = min(tup[current], tup[to]);
                if ((tup[to] >= tin[current] && parent != -1) || (parent == -1 && children > 1)) {
                    isArticulationPoint[current] = 1;
                    extractComponent(to, current);
                }
            }
            else {
                tup[current] = min(tup[current], tin[to]);
            }
        }
        if (parent == -1)
            extractComponent(current, -1);
    }

    void extractComponent(int subTreeRoot, int current) {
        biconnectedComponents.emplace_back();
        vector<int>& comp = biconnectedComponents.back();
        if (current != -1)
            comp.push_back(current);
        while (true) {
            int x = buffer.top();
            buffer.pop();
            comp.push_back(x);
            if (x == subTreeRoot)
                return;
        }
    }

    void findPointsAndComponents() {
        for (int u = 0; u < vertexCount; u++)
            if (!visited[u])
                dfs(u);
        for (int i = 0; i < vertexCount; i++)
            if (isArticulationPoint[i])
                articulationPoints.push_back(i);
    }
};
