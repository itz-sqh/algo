#include <bits/stdc++.h>
#include "NumberTheory/Utils/Modint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"
using namespace std;
constexpr int MOD = 998244353;
using Mint = Modint<MOD>;
using polynom = ModintPolynomial<Mint>;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<polynom> p(n);
    multiset<polynom, decltype([](const polynom& a, const polynom& b) {return a.deg() < b.deg();})> st = {polynom(1)};
    int d = 0;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        d += x;
        vector<Mint> a(x + 1);
        for (auto& y :a) cin >> y;
        st.insert(polynom(a));
    }
    while (st.size() > 1) {
        auto it = st.begin();
        auto P = *it;
        st.erase(it);
        it = st.begin();
        auto Q = *it;
        st.erase(it);
        st.insert(P * Q);
    }
    st.begin()->print(d + 1);
}