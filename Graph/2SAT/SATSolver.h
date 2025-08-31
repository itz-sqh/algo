#pragma once
#include <bits/stdc++.h>


using namespace std;

struct SATSolver{
    // Solves 2-SAT problem using Kosaraju's algorithm for SCC
    // Time: O(n + m) where n is number of variables and m is number of clauses
    // Space: O(n + m)
    // 2 Sat https://judge.yosupo.jp/submission/311202
    int variableCount;
    int vertexCount;
    vector<vector<int>> graph;
    vector<vector<int>> reversedGraph;
    vector<int> component;
    vector<int> order;
    vector<int> visited;

    explicit SATSolver(int variableCount) : variableCount(variableCount), vertexCount(2 * variableCount),
                                            graph(vertexCount),
                                            reversedGraph(vertexCount), component(vertexCount), visited(vertexCount, 0){
        order.reserve(vertexCount);
    }

    int getNode(int var, bool negated) const{
        return negated ? var + variableCount : var;
    }

    void addEdge(int u, int v){
        graph[u].push_back(v);
        reversedGraph[v].push_back(u);
    }

    // One of them is true
    void addOr(int u, bool negateU, int v, bool negateV){
        addEdge(getNode(u, !negateU), getNode(v, negateV));
        addEdge(getNode(v, !negateV), getNode(u, negateU));
    }

    // Only one of them is true
    void addXor(int u, bool negateU, int v, bool negateV){
        addOr(u, negateU, v, negateV);
        addOr(u, !negateU, v, !negateV);
    }

    // Both of them have the same value
    void addAnd(int u, bool negateU, int v, bool negateV){
        addXor(u, !negateU, v, negateV);
    }

    // First and second are not true and false respectively
    void addImpl(int u, bool negateU, int v, bool negateV){
        addOr(u, !negateU, v, negateV);
    }


    void dfs(int start){
        visited[start] = true;
        for (int to : graph[start])
            if (!visited[to])
                dfs(to);
        order.push_back(start);
    }

    void scc(int start, int id){
        visited[start] = true;
        component[start] = id;

        for (int to : reversedGraph[start])
            if (!visited[to])
                scc(to, id);
    }

    vector<int> solve(){
        // Topological sort
        for (int i = 0; i < vertexCount; i++)
            if (!visited[i])
                dfs(i);

        // Strongly connected components
        visited.assign(vertexCount, false);
        int id = 0;
        for (int i = vertexCount - 1; i >= 0; i--)
            if (!visited[order[i]])
                scc(order[i], id++);

        // Construct the answer
        vector<int> res(variableCount);
        for (int i = 0; i < variableCount; i++){
            if (component[i] == component[i + variableCount]) return {};
            res[i] = component[i] > component[i + variableCount];
        }
        return res;
    }
};