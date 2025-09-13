#include <bits/stdc++.h>
#include "NumberTheory/Utils/Quotient.h"
#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    vector<long long> res = Quotient::allQuotients(n);
    cout << res.size() << endl;
    for (auto x: res)
        cout << x << " ";
}
