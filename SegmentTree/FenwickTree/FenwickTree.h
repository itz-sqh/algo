#pragma once

#include<vector>
using namespace std;


struct Fenwick {
    size_t n;
    vector<long long> bit;
    explicit Fenwick(const vector<int>& a) : n(a.size()), bit(n) {
        vector<int> pref(n+1);
        pref[0] = 0;
        for (int i = 0; i < n; i++)
            pref[i+1] = pref[i] + a[i];
        for (int i = 0; i < n; i++)
            bit[i] = pref[i+1] - pref[i & (i+1)];
    }
    [[nodiscard]] long long sum(int r) const {
        long long res = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            res += bit[r];
        return res;
    }
    [[nodiscard]] long long sum(int l, int r) const {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};