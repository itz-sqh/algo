#include <bits/stdc++.h>
#include "NumberTheory/Sequences/Sequences.h"
#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    auto res = Sequences::bellNumber(n);
    for (auto x : res)
        cout << x << " ";
}
