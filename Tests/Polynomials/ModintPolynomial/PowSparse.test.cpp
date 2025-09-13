#include <bits/stdc++.h>
#include "NumberTheory/Utils/Mint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse"
constexpr long long MOD = 998244353;

using polynom = ModintPolynomial<Mint>;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Mint::MOD = MOD;
    long long n, k, m;
    cin >> n >> k >> m;
    vector<Mint> a(n);
    for (int i = 0; i < k; i++) {
        int idx;
        cin >> idx;
        cin >> a[idx];
    }
    polynom p(a);
    p.pow(m, n).print(n);
}