#pragma once
#include <bits/stdc++.h>

using namespace std;

template <class T = int>
struct Node{
    // node for segment tree
    // override everything based on task
    T value;
    explicit Node(T val) : value(val){}
    // for default node
    explicit Node() : value(0){}
    // + - merge nodes
    Node operator+(const Node& other) const{
        return Node{value + other.value};
    }
};

template <class T = int>
struct SegmentTree{
    // Default segment tree
    // Time : build - O(n) update, query - O(log(n))
    // Space: build - O(n)  update, query - O(1)
    // Static Range Sum    : https://judge.yosupo.jp/submission/311302
    // Static RMQ          : https://judge.yosupo.jp/submission/311305
    // Point Add Range Sum : https://judge.yosupo.jp/submission/311307
    // Sum segment tree    : https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/submission/336262257
    // Find k-th one       : https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/submission/336262107
    unordered_map<int, Node<T>> tree;
    int n;

    explicit SegmentTree(const int n) : n(n){
        tree.reserve(4 * n + 1);
    }

    explicit SegmentTree(const vector<T>& a) : n(a.size()){
        tree.reserve(4 * n + 1);
        init(1, 0, n, a);
    }

    void update(int ind, T val){
        // a[ind] = val, 0 <= ind < n
        return update(1, 0, n, ind, val);
    }

    Node<T> query(int ql, int qr){
        // [ql, qr) , 0 <= ql,qr < n
        return query(1, 0, n, ql, qr);
    }

    int findKthOne(int k) const{
        //a contains only 1 or 0
        if (k < 0 || k >= query(0, n).value){
            return -1;
        }
        return find_kth_one(1, 0, n, k);
    }

    void init(int ind, int l, int r, const vector<T>& a){
        if (l + 1 == r){
            tree[ind] = Node(a[l]);
            return;
        }
        int m = (l + r) / 2;
        init(2 * ind, l, m, a);
        init(2 * ind + 1, m, r, a);
        tree[ind] = tree[2 * ind] + tree[2 * ind + 1];
    }

    void update(int ind, int l, int r, int i, T val){
        if (i < l || i >= r) return;
        if (l + 1 == r){
            tree[ind] = Node(val);
            return;
        }
        int m = (l + r) / 2;
        update(2 * ind, l, m, i, val);
        update(2 * ind + 1, m, r, i, val);
        tree[ind] = tree[2 * ind] + tree[2 * ind + 1];
    }

    Node<T> query(int ind, int l, int r, int ql, int qr){
        if (qr <= l || ql >= r) return Node<T>();
        if (ql <= l && r <= qr) return tree[ind];
        int m = (l + r) / 2;
        Node<T> left = query(2 * ind, l, m, ql, qr);
        Node<T> right = query(2 * ind + 1, m, r, ql, qr);
        return left + right;
    }

    int find_kth_one(int ind, int l, int r, int k){
        if (l + 1 == r) return l;
        int m = (l + r) / 2;
        int left_count = tree[2 * ind].value;
        if (k < left_count) return find_kth_one(2 * ind, l, m, k);
        return find_kth_one(2 * ind + 1, m, r, k - left_count);
    }
};