#include <bits/stdc++.h>
#include "NumberTheory/Utils/FactorialFast.h"
#include "NumberTheory/Utils/Mint.h"
#define PROBLEM "https://judge.yosupo.jp/problem/many_factorials"
constexpr long long MOD = 998244353;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Mint::MOD = MOD;
    FactorialFast<Mint> fast(10);
    int q;
    cin >> q;
    while (q--) {
        long long n;
        cin >> n;
        cout << fast.fact(n) << endl;
    }
}
