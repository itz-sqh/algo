#pragma once
#include <bits/stdc++.h>

using namespace std;

struct DSU{
    //DSU
    // Time : build - O(n*log(n)), query - O(log(n))
    // Space: O(n*log(n))
    vector<int> rank;
    vector<int> parent;

    explicit DSU(const int n){
        rank.resize(n);
        parent.resize(n);
        for (int i = 0; i < n; i++){
            makeSet(i);
        }
    }

    void makeSet(const int v){
        parent[v] = v;
        rank[v] = 1;
    }

    int findSet(int u){
        if (u == parent[u])
            return u;
        return parent[u] = findSet(parent[u]);
    }

    void unionSet(int u, int v){
        v = findSet(v);
        u = findSet(u);
        if (v == u) return;
        if (rank[u] < rank[v])
            swap(v, u);
        parent[v] = u;
        if (rank[v] == rank[u])
            ++rank[u];
    }
};
