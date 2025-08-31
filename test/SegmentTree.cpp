#include "../SegmentTree/SegmentTree.h"
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#define int long long

int32_t main(){
    // Example usage
    /* sum on segment*/
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& el : a)
        cin >> el;
    SegmentTree tree(a);
    while (q--){
        int op;
        cin >> op;
        if (op == 1){
            int ind, val;
            cin >> ind >> val;
            tree.update(ind, val);
        }
        if (op == 2){
            int l, r;
            cin >> l >> r;
            cout << tree.query(l, r).value << endl;
        }
    }
}
