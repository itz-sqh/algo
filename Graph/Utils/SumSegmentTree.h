#pragma once
#include <bits/stdc++.h>

using namespace std;

struct SumSegmentTree {
    // Default segment tree for sum
    vector<long long> tree;
    int n;

    explicit SumSegmentTree(const int n) :
        n(n) {
        tree.resize(4 * n + 1);
    }

    explicit SumSegmentTree(const vector<long long>& a) :
        n(a.size()) {
        tree.resize(4 * n + 1);
        build(1, 0, n, a);
    }

    void init(const vector<long long>& a) {
        build(1, 0, n, a);
    }

    void build(int ind, int l, int r, const vector<long long>& a) {
        if (l + 1 == r) {
            tree[ind] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * ind, l, m, a);
        build(2 * ind + 1, m, r, a);
        tree[ind] = tree[2 * ind] + tree[2 * ind + 1];
    }

    void update(int ind, int val) {
        // a[ind] = val, 0 <= ind < n
        return update(1, 0, n, ind, val);
    }

    int query(int ql, int qr) {
        // [ql, qr) , 0 <= ql,qr < n
        return query(1, 0, n, ql, qr);
    }

    void update(int ind, int l, int r, int i, int val) {
        if (i < l || i >= r)
            return;
        if (l + 1 == r) {
            tree[ind] = val;
            return;
        }
        int m = (l + r) / 2;
        update(2 * ind, l, m, i, val);
        update(2 * ind + 1, m, r, i, val);
        tree[ind] = tree[2 * ind] + tree[2 * ind + 1];
    }

    int query(int ind, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r)
            return 0;
        if (ql <= l && r <= qr)
            return tree[ind];
        int m = (l + r) / 2;
        return query(2 * ind, l, m, ql, qr) + query(2 * ind + 1, m, r, ql, qr);
    }
};
