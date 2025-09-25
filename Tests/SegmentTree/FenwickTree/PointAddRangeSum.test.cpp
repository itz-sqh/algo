#include <iostream>
#include "SegmentTree/FenwickTree/FenwickTree.h"
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    Fenwick fenwick(a);
    for (int i = 0; i < q; i++) {
        int c; cin >> c;
        if (c== 1) {
            int l, r; cin >> l >> r;
            cout << fenwick.sum(l, r) << endl;
        }
        else {
            int id, val;
            cin >> id >> val;
            fenwick.add(id,val);
        }
    }
}