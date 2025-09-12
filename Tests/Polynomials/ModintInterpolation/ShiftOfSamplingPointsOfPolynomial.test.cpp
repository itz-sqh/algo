#include <bits/stdc++.h>
#include "NumberTheory/Utils/Modint.h"
#include "Polynomials/ModintInterpolation/ModintInterpolation.h"
#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"
using namespace std;
constexpr unsigned long long MOD = 998244353;
using Mint = Modint<MOD>;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, c;
    cin >> n >> m >> c;
    vector<Mint> a(n);
    for (auto& x : a) cin >> x;
    auto res = Interpolation::consecutivePointsInterpolation<Mint, double>(a, m ,c);
    for (auto x : res) cout << x << " ";
    return 0;
}