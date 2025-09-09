#include "NumberTheory/PrimalityTest/MillerRabin.h"
#include <bits/stdc++.h>

using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        long long n; cin >> n;
        cout << (MillerRabin::isPrime(n) ? "Yes" : "No") << endl;
    }
}
