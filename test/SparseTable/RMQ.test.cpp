#include "../../SparseTable/SparceTable.h"
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& it : a) cin >> it;
    SparseTable table(a);
    while (q--){
        int l, r;
        cin >> l >> r;
        cout << table.getMin(l, r) << endl;
    }
}
