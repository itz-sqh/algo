#include "NumberTheory/Utils/Modint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse"
constexpr long long MOD = 998244353;

using mint = Modint<MOD>;
using polynom = ModintPolynomial<mint>;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k;
    cin >> n >> k;
    vector<mint> a(n);
    for (int i = 0; i < k; i++) {
        int idx;
        cin >> idx;
        cin >> a[idx];
    }
    polynom p(a);
    p.exp(n).print(n);
}