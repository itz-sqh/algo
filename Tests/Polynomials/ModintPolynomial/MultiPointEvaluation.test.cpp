#include <bits/stdc++.h>
#include "NumberTheory/Utils/Mint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"
using namespace std;
constexpr unsigned long long MOD = 998244353;
using Mint = Modint<MOD>;
using polynom = ModintPolynomial<Mint>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<Mint> c(n), p(m);
    for (auto& x : c) cin >> x;
    for (auto& x : p) cin >> x;
    for (auto x : polynom(c).evaluate(p)) cout << x << " ";
}
