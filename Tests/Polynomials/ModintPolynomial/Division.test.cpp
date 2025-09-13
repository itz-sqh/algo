#include "NumberTheory/Utils/Mint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"
constexpr long long MOD = 998244353;

using polynom = ModintPolynomial<Mint>;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Mint::MOD = MOD;
    long long n, m;
    cin >> n >> m;
    vector<Mint> a(n);
    vector<Mint> b(m);
    for (auto& x: a)
        cin >> x;
    for (auto& x: b)
        cin >> x;
    polynom p(a);
    polynom q(b);
    auto res = p.divMod(q);
    cout << res.first.size() << " " << res.second.size() << endl;
    res.first.print(res.first.size());
    res.second.print(res.second.size());
}