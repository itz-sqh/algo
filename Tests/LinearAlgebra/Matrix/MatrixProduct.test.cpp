#include <iostream>
#include "NumberTheory/Utils/Mint.h"
#include "LinearAlgebra/Matrix/Matrix.h"
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n,m,k; cin >> n >> m >> k;
    Matrix<Mint> A(n,m), B(m,k);
    cin >> A >> B;
    cout << A*B;
}