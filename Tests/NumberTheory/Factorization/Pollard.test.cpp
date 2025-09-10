#include "NumberTheory/Factorization/Pollard.h"
#include <bits/stdc++.h>
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        auto factors = Pollard::factorize(n);
        int size = 0;
        for (const auto& [factor, power] : factors)
            size += power;
        cout << size << " ";
        for (const auto& [factor, power]: factors)
            for (int i = 0; i < power; i++)
                cout << factor << " ";
        cout << endl;
    }
}
