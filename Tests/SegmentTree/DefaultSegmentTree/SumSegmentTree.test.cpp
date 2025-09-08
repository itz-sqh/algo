#include "SumSegmentTree.h"
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x: a)
        cin >> x;
    SumSegmentTree tree(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << tree.query(l, r) << endl;
    }
}
