#include "NumberTheory/Utils/Mint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"
constexpr long long MOD = 998244353;

using polynom = ModintPolynomial<Mint>;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Mint::MOD = MOD;
    long long n;
    cin >> n;
    vector<Mint> a(n);
    for (auto& x: a)
        cin >> x;
    polynom p(a);
    p.inverse(n).print(n);
}
