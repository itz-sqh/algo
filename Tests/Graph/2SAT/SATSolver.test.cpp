#include "Graph/2SAT/SATSolver.h"
#include <bits/stdc++.h>
#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s >> s;
    int n, m;
    cin >> n >> m;

    SATSolver solver(n);
    for (int i = 0; i < m; i++) {
        int a, b, zero;
        cin >> a >> b >> zero;

        int u = abs(a) - 1;
        bool negateU = (a < 0);
        int v = abs(b) - 1;
        bool negateV = (b < 0);

        solver.addOr(u, negateU, v, negateV);
    }

    vector<int> solution = solver.solve();

    if (solution.empty()) {
        cout << "s UNSATISFIABLE" << endl;
    }
    else {
        cout << "s SATISFIABLE" << endl;
        cout << "v ";
        for (int i = 0; i < n; i++) {
            if (solution[i]) {
                cout << (i + 1) << " ";
            }
            else {
                cout << -(i + 1) << " ";
            }
        }
        cout << "0" << endl;
    }
}
