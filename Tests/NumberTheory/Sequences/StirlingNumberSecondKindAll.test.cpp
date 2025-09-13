#include <bits/stdc++.h>
#include "NumberTheory/Sequences/Sequences.h"
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    for (auto x : Sequences::stirlingSecondKindAll(n))
        cout << x << " ";
}
