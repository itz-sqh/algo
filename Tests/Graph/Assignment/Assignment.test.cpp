#include<iostream>
#include "Graph/Assignment/Assignment.h"
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    Assignment assignment(n,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c; cin >> c;
            assignment.addCost(i,j,c);
        }
    }
    auto [cost, p] = assignment.assign();
    cout << cost << endl;
    for (auto x : p) cout << x << " ";

}