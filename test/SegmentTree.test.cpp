#include "../SegmentTree/SegmentTree.h"
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#define int long long

int32_t main(){
    // Example usage
    /* sum on segment*/
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    SegmentTree st(a);
    while (q--){
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r).value << endl;
    }
}
