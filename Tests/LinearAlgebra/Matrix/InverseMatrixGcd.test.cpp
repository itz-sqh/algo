#include <iostream>
#include "NumberTheory/Utils/Mint.h"
#include "LinearAlgebra/Matrix/Matrix.h"
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n, m; cin >> n;
    Matrix<Mint> A(n,n);
    cin >> A;
    auto [det, invA] = A.gcdinv();
    if (det == 0) cout << -1;
    else cout << invA;
}