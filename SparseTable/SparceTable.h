#pragma once
#include <bits/stdc++.h>

using namespace std;

struct SparseTable {
    // Sparse Table for Range Minimum(Maximum) Query (RMQ)
    // query on [l;r) 0 <= l,r < n
    // Time  : Preprocessing - O(n * log(n)), Query - O(1)
    // Space : O(n * log(n))
    vector<vector<int>> tableMin, tableMax;
    vector<int> logTable;
    int n;
    int logN;

    SparseTable() :
        n(0), logN(0) {}

    explicit SparseTable(const vector<int>& a) :
        n(a.size()) {
        logN = ceil(log2(n)) + 1;
        tableMin.assign(n, vector<int>(logN, -1));
        tableMax.assign(n, vector<int>(logN, -1));
        logTable.assign(n + 1, 0);
        for (int i = 0; i < n; i++)
            tableMin[i][0] = tableMax[i][0] = a[i];
        for (int k = 1, step = 1; k < logN; k++, step *= 2) {
            for (int i = 0; i < n; i++) {
                tableMin[i][k] = min(tableMin[i][k - 1], tableMin[min(i + step, n - 1)][k - 1]);
                tableMax[i][k] = max(tableMax[i][k - 1], tableMax[min(i + step, n - 1)][k - 1]);
            }
        }
        for (int i = 2; i <= n; i++)
            logTable[i] = logTable[i / 2] + 1;
    }

    int getMin(const int l, const int r) const {
        const int step = logTable[r - l];
        return min(tableMin[l][step], tableMin[r - (1 << step)][step]);
    }

    int getMax(const int l, const int r) const {
        const int step = logTable[r - l];
        return max(tableMax[l][step], tableMax[r - (1 << step)][step]);
    }
};
