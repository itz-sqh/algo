#pragma once
#include <vector>
#include "NumberTheory/Factorials/Factorial.h"
#include "Polynomials/FFT/FFT.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"
using namespace std;
namespace Interpolation {
    template <typename Mint, typename ftype = double>
    vector<Mint> consecutivePointsInterpolation(const vector<Mint>& f, int m, long long c) {
        // Given f(0), f(1), ... f(n - 1) compute f(c), f(c + 1), ... f(c + m - 1)
        // deg(f) < n
        // https://suisen-cp.github.io/cp-library-cpp/library/polynomial/shift_of_sampling_points.hpp.html
        // https://codeforces.com/blog/entry/115696
        // Time : O((n + m) * log(n + m))
        // Space : O(n + m)
        int n = static_cast<int>(f.size());
        if (n == 0 || m <= 0) return vector<Mint>(max(0, m), Mint(0));
        using F = Factorial<Mint>;

        vector<Mint> p(n), q(n);
        for (int i = 0; i < n; i++) {
            p[i] = f[i] * F::ifact(i);
            q[i] = (i % 2 ? Mint(-1) : Mint(1)) * F::ifact(i);
        }

        auto conv1 = fft::convolution<Mint, ftype>(p, q);
        conv1.resize(n);

        vector<Mint> rev(n);
        for (int i = 0; i < n; i++)
            rev[i] = conv1[n - 1 - i] * F::fact(n - 1 - i);


        vector<Mint> binom(n);
        binom[0] = 1;
        Mint prod = 1;
        for (int i = 1; i < n; i++) {
            prod *= Mint(c - (i - 1));
            binom[i] = prod * F::ifact(i);
        }

        auto conv2 = fft::convolution<Mint, ftype>(rev, binom);
        conv2.resize(2 * n - 1);

        vector<Mint> g1(n), g2(m);
        for (int i = 0; i < n; i++) g1[i] = conv2[n - 1 - i] * F::ifact(i);
        for (int i = 0; i < m; i++) g2[i] = F::ifact(i);

        auto conv3 = fft::convolution<Mint, ftype>(g1, g2);
        conv3.resize(n + m - 1);

        vector<Mint> res(m);
        for (int i = 0; i < m; i++) {
            if (i < static_cast<int>(conv3.size())) res[i] = F::fact(i) * conv3[i];
        }
        return res;
    }

    template<typename Mint, typename ftype = double>
    ModintPolynomial<Mint, ftype> interpolate(const vector<Mint>& x, const vector<Mint>& y) {
        // Interpolates polynomial from (xi, yi) pairs
        // https://cp-algorithms.com/algebra/polynomial.html#interpolation
        using polynom = ModintPolynomial<Mint, ftype>;
        int n = x.size();
        assert(n == y.size());
        vector<polynom> tree(4 * n);
        polynom::build(tree, x, 1, 0, n);

        auto inter = [&](auto&& self, int v, int l, int r) -> polynom {
            if (r - l == 1) return polynom(y[l] / tree[1].derivative().evaluate(x[l]));
            int m = (l + r) / 2;
            return self(self, 2 * v, l, m) * tree[2 * v + 1]
            + self(self, 2 * v + 1, m, r) * tree[2 * v];
        };
        return inter(inter, 1, 0, n);
    }
}