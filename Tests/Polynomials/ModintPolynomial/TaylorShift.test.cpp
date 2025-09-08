#include "NumberTheory/Utils/Modint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"
constexpr long long MOD = 998244353;

using mint = Modint<MOD>;
using polynom = ModintPolynomial<mint>;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, c;
    cin >> n >> c;
    vector<mint> a(n);
    for (auto& x: a)
        cin >> x;
    polynom p(a);
    p.taylorShift(c).print(n);
}
