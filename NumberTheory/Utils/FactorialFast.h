#pragma once
#include <vector>
#include "NumberTheory/Utils/Factorial.h"
#include "Polynomials/ModintInterpolation/ModintInterpolation.h"
using namespace std;
template<typename Modint, typename ftype = double>
class FactorialFast {
    // Computes factorials for large numbers
    // Time : build O(2^K * K + MOD / 2^K), query O(2^K)
    // Space : O(2^K + MOD / 2^K)
private:
    long long P;
    const int K;
    vector<Modint> fact_;
public:
    explicit FactorialFast(int K = 9) : P(Modint::mod()), K(K) {
        vector<Modint> Y = {1};
        Factorial<Modint> F;

        for (int i = 0; i < K; i++) {
            vector<Modint> Z = Interpolation::consecutivePointsInterpolation<Modint, ftype>(Y, 1 << (i + 2), 0);
            Y.resize(1 << (i + 1));
            for (int j = 0; j < (1 << (i + 1)); j++)
                Y[j] = Z[2 * j] * Z[2 * j + 1] * Modint((1 << i) * (2 * j + 1));
        }

        vector<Modint> Z = Interpolation::consecutivePointsInterpolation<Modint, ftype>(Y, P / (1 << K), 0);
        fact_.resize(P / (1 << K) + 1);
        fact_[0] = 1;
        for (size_t i = 0; i < Z.size(); i++)
            fact_[i + 1] = fact_[i] * Z[i] * Modint((i + 1) * (1 << K));
    }
    Modint fact(long long n) {
        if (n < P) {
            Modint res = fact_[n / (1 << K)];
            for (long long i = n / (1 << K) * (1 << K) + 1; i <= n; i++)
                res *= Modint(i);
            return res;
        }
        return 0;
    }
    Modint ifact(long long n) {
        return fact(n).inv();
    }
};