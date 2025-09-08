#include "NumberTheory/Utils/Modint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"
constexpr long long MOD = 998244353;

using mint = Modint<MOD>;
using polynom = ModintPolynomial<mint>;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<mint> a(n);
    for (auto& x: a)
        cin >> x;
    polynom p(a);
    p.log(n).print(n);
}
