#pragma once
#include <algorithm>
#include <vector>

namespace Quotient {
    // Find all values of floor(n/x) for 1 <= x <= N
    // Time : O(sqrt(n) * log(n)), O(sqrt(n)) without sorting
    // Space : O(sqrt(n))
    inline std::vector<long long> allQuotients(long long n) {
        std::vector<long long> res;
        for (long long l = 1, r = 1; l <= n; l = r + 1) {
            r = n / (n / l);
            res.push_back(n / l);
        }
        sort(res.begin(), res.end());
        return res;
    }
} // namespace Quotient
