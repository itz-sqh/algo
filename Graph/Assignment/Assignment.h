#pragma once
#include <vector>
using namespace std;


struct Assignment {
    // Solves assignment problem i.e. finds permutation p s.t. sum(a[i][p[i]]) is minimal
    // Time : O(n^2 * m)
    // Space : O(n * m)
    int n, m;
    vector<vector<int>> cost;
    vector<int> matching;
    static constexpr int inf = 1e9;

    Assignment(int n, int m) : n(n), m(m), cost(n, vector<int>(m)), matching(m,-1) {}

    void addCost(int i, int j, int c) {
        cost[i][j] = c;
    }

    pair<long long, vector<int>> assign() {
        vector<int> a(n), b(m);
        vector<int> p(m, -1);
        for (int v = 0; v < n; ++v) {
            vector<int> mn(m, inf);
            vector<bool> Rplus(m);
            vector<bool> Lplus(n);
            Lplus[v] = true;
            int u = -1;
            p.assign(m, -1);
            for (int j = 0; j < m; j++) {
                mn[j] = cost[v][j] + a[v] + b[j];
                p[j] = v;
            }
            while (true) {
                int delta = inf;
                int mnj = -1;
                for (int j = 0; j < m; j++) {
                    if (!Rplus[j] && mn[j] < delta) {
                        delta = mn[j];
                        mnj = j;
                    }
                }
                for (int i = 0; i < n; i++)
                    if (Lplus[i])
                        a[i] -= delta;
                for (int j = 0; j < m; j++) {
                    if (Rplus[j]) b[j] += delta;
                    else mn[j] -= delta;
                }
                Rplus[mnj] = true;
                u = matching[mnj];
                if (u == -1) {
                    int j = mnj;
                    while (j != -1) {
                        int i = p[j];
                        int nxt = -1;
                        for (int k = 0; k < m; k++) {
                            if (matching[k] == i) {
                                nxt = k;
                                break;
                            }
                        }
                        matching[j] = i;
                        j = nxt;
                    }
                    break;
                }
                else {
                    Lplus[u] = true;
                    for (int j = 0; j < m; j++) {
                        if (!Rplus[j]) {
                            int val = cost[u][j] + a[u] + b[j];
                            if (val < mn[j]) {
                                mn[j] = val;
                                p[j] = u;
                            }
                        }
                    }
                }
            }
        }
        long long c = 0;
        vector<int> res(n, -1);
        for (int j = 0; j < m; j++) {
            if (matching[j] != -1) {
                res[matching[j]] = j;
                c += cost[matching[j]][j];
            }
        }

        return {c, res};
    }
};