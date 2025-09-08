#include "SegmentTree/DefaultSegmentTree/SegmentTree.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x: a)
        cin >> x;
    SegmentTree st(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r).value << endl;
    }
}
