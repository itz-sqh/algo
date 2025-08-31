#pragma once
#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    // optional parameter
    int index;
    Edge(int from, int to, int weight, int index = 0) : from(from), to(to), weight(weight), index(index) {}
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

struct MST {
    // Finds MST in undirected graph
    // Time: O(m * log(m)) can be done in O(m * log(n)) or O(n^2) using array instead of heap
    // Space: O(n + m)
    // Minimum Spanning Tree : https://judge.yosupo.jp/submission/311571
    vector<vector<Edge>> graph;
    int vertexCount;
    int edgeCount;

    MST(int vertexCount) : vertexCount(vertexCount), graph(vertexCount) {}

    void addAdge(int from, int to, int weight, int index = 0) {
        graph[from].emplace_back(from, to, weight, index);
        graph[to].emplace_back(to, from, weight, index);
        edgeCount++;
    }

    vector<Edge> buildMST(int start = 0) {
        priority_queue<Edge, vector<Edge>, greater<>> pq;
        vector<int> selected(vertexCount, false);
        vector<Edge> mst;

        selected[start] = true;
        for (Edge edge : graph[start]) {
            pq.push(edge);
        }

        while (!pq.empty()) {
            Edge current = pq.top();
            pq.pop();
            int to = current.to;
            if (selected[to])
                continue;
            selected[to] = true;
            mst.emplace_back(current);
            for (Edge edge : graph[to])
                if (!selected[edge.to])
                    pq.push(edge);
        }
        return mst;
    }
};