#include <bits/stdc++.h>
#include "NumberTheory/Sequences/Sequences.h"
#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    Mint::MOD = m;
    auto res = Sequences::subFactorial(n);
    for (int i = 1; i <= n; ++i) cout << res[i] << ' ';
}
