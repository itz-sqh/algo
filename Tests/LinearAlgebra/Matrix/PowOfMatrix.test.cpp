#include <iostream>
#include "NumberTheory/Utils/Mint.h"
#include "LinearAlgebra/Matrix/Matrix.h"
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n, m; cin >> n >> m;
    Matrix<Mint> A(n,n);
    cin >> A;
    cout << A.pow(m);
}