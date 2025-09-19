#include<iostream>
#include "LinearAlgebra/Matrix/Matrix.h"
#include "NumberTheory/Utils/Mint.h"
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n,m; cin >> n >> m;
    Matrix<Mint> A(n,n);
    cin >> A;
    cout << A.rank();
}