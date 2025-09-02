#pragma once
#include<bits/stdc++.h>
#include "../Utils/Edge.h"

using namespace std;


struct MST {
    // Finds MST in undirected graph
    // Time: O(m * log(n)) can be done in O(n^2) using array instead of heap
    // Space: O(n + m)
    vector<vector<Edge>> graph;
    int vertexCount;

    explicit MST(int vertexCount) : vertexCount(vertexCount), graph(vertexCount) {}

    void addAdge(int from, int to, int weight, int index = 0) {
        graph[from].emplace_back(from, to, weight, index);
        graph[to].emplace_back(to, from, weight, index);
    }

    vector<Edge> buildMST(int start = 0) {
        priority_queue<Edge, vector<Edge>, greater<>> pq;
        vector<int> selected(vertexCount, false);
        vector<Edge> mst;

        selected[start] = true;
        for (const Edge& edge : graph[start]) {
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
            for (const Edge& edge : graph[to])
                if (!selected[edge.to])
                    pq.push(edge);
        }
        return mst;
    }
};