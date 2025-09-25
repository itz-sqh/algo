#include <iostream>
#include "NumberTheory/Utils/Mint.h"
#include "LinearAlgebra/Matrix/Matrix.h"
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n, m; cin >> n >> m;
    Mint::MOD = m;
    Matrix<Mint> A(n,n);
    cin >> A;
    cout << A.gcddet();
}