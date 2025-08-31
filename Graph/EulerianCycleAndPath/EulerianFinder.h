#pragma once
#include <bits/stdc++.h>

using namespace std;

struct EulerianFinder{
    //Check for and find Eulerian paths and cycles in directed or undirected graphs with self-loops and parallel edges
    // Time : check - O(n), find - O(m)   without copy graph [O(n+m)]
    // Space: check - O(1), find - O(n+m) without copy graph [O(n+m)]
    const vector<vector<int>> mainGraph;
    vector<int> inDegree, outDegree;
    int vertexCount{};
    vector<int> selfLoops;
    int edgeCount{};
    bool isDirected;

    EulerianFinder(const vector<vector<int>>& graph, bool directed) : mainGraph(graph), isDirected(directed){
        vertexCount = graph.size();
        inDegree.assign(vertexCount, 0);
        outDegree.assign(vertexCount, 0);
        selfLoops.assign(vertexCount, 0);

        for (int from = 0; from < vertexCount; from++){
            for (int to : graph[from]){
                if (to == from) selfLoops[from]++;
                outDegree[from]++;
                inDegree[to]++;
                edgeCount++;
            }
        }
        if (!isDirected) edgeCount /= 2;
    }

    bool hasEulerianCycle() const{
        if (isDirected){
            for (int u = 0; u < vertexCount; u++)
                if (outDegree[u] != inDegree[u])
                    return false;
        }
        else{
            for (int u = 0; u < vertexCount; u++)
                if ((mainGraph[u].size() - selfLoops[u]) % 2 == 1)
                    return false;
        }
        return true;
    }

    bool hasEulerianPath() const{
        if (isDirected){
            int start = 0, end = 0;
            for (int u = 0; u < vertexCount; u++){
                if (outDegree[u] - inDegree[u] == 1)
                    start++;
                else if (outDegree[u] - inDegree[u] == -1)
                    end++;
                else if (outDegree[u] != inDegree[u])
                    return false;
            }
            return (start + end == 0) || (start == 1 && end == 1);
        }
        int cnt = 0;
        for (int u = 0; u < vertexCount; u++)
            if ((mainGraph[u].size() - selfLoops[u]) % 2 == 1)
                cnt++;
        return cnt == 0 || cnt == 2;
    }

    int findStartVertex() const{
        int start = 0;
        if (isDirected){
            for (int u = 0; u < vertexCount; u++){
                if (outDegree[u] - inDegree[u] == 1)
                    return u;
                if (outDegree[u] + inDegree[u] != 0)
                    start = u;
            }
        }
        else{
            for (int u = 0; u < vertexCount; u++){
                if ((mainGraph[u].size() - selfLoops[u]) % 2 == 1)
                    return u;
                if (!mainGraph[u].empty())
                    start = u;
            }
        }
        return start;
    }

    void dfs(int u, vector<int>& path, vector<unordered_multiset<int>>& graph){
        auto& edges = graph[u];
        while (!edges.empty()){
            int to = *edges.begin();
            edges.erase(edges.begin());
            if (!isDirected)
                graph[to].erase(graph[to].find(u));
            dfs(to, path, graph);
        }
        path.push_back(u);
    }

    vector<int> findEulerianPath(){
        if (!hasEulerianPath())
            return {};
        int start = findStartVertex();
        vector<int> path;
        vector<unordered_multiset<int>> copyGraph(vertexCount);
        for (int from = 0; from < vertexCount; from++)
            for (int to : mainGraph[from])
                copyGraph[from].insert(to);
        dfs(start, path, copyGraph);
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> findEulerianCycle(){
        if (!hasEulerianCycle())
            return {};
        return findEulerianPath();
    }
};
