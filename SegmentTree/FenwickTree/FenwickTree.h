#pragma once
#include<vector>
using namespace std;
struct Fenwick {
    size_t n;
    vector<long long> bit;
    explicit Fenwick(const vector<int>& a) : n(a.size()), bit(n) {
        for (int i = 0; i < n; i++) {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }
    long long sum(int r) const {
        long long res = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            res += bit[r];
        return res;
    }
    long long sum(int l, int r) const {
        return sum(r - 1) - sum(l - 1);
    }
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
    void add(int l, int r, int delta) {
        add(l,delta);
        add(r,-delta);
    }
};