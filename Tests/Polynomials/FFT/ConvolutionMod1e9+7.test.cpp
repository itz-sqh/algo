#include <bits/stdc++.h>
#include "NumberTheory/Utils/Mint.h"
#include "Polynomials/FFT/FFT.h"
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

constexpr unsigned long long MOD = 1e9 + 7;
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Mint::MOD = MOD;
    int n, m; cin >> n >> m;
    vector<Mint> a(n), b(m);
    for (auto& x :a) cin >> x;
    for (auto& x : b) cin >> x;
    fft::mul<Mint, long double>(a, b);
    for (int i = 0; i < n + m - 1; i++) {
        cout << a[i] << " ";
    }
}