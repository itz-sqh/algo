#include <bits/stdc++.h>
#include "NumberTheory/Utils/Binomial.h"
#include "NumberTheory/Utils/Mint.h"
#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q, m;
    cin >> q >> m;
    Mint::MOD = m;
    while (q--) {
        long long n, k;
        cin >> n >> k;
        cout << Binomial::C<Mint>(n, k) << endl;
    }
}
