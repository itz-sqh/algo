#include <bits/stdc++.h>
#include "NumberTheory/Sequences/Sequences.h"
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_fixed_k"
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    for (auto x : Sequences::stirlingSecondKindFixedK(n, k))
        cout << x << " ";
}
