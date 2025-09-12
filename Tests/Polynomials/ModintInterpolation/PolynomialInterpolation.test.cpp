#include <bits/stdc++.h>
#include "NumberTheory/Utils/Modint.h"
#include "Polynomials/ModintInterpolation/ModintInterpolation.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"
using namespace std;

constexpr unsigned long long MOD = 998244353;
using Mint = Modint<MOD>;
using polynom = ModintPolynomial<Mint>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<Mint> x(n), y(n);
    for (auto& val : x) cin >> val;
    for (auto& val : y) cin >> val;
    Interpolation::interpolate(x, y).print(n);
}
