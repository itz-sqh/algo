#pragma once
#include <vector>
#include "NumberTheory/Utils/Mint.h"
#include "Polynomials/ModintPolynomial/ModintPolynomial.h"

namespace Sequences {
    using namespace std;

    inline vector<Mint> stirlingFirstKindAll(int n) {
        // Computes Stirling numbers of the first kind s(n,k) for all 0 ≤ k ≤ n
        // Pₙ(x) = x(x + 1)(x + 2)⋯(x + n - 1) = ∑ₖ s(n,k) xᵏ
        // Time : O(n * log^2(n))
        // Space : O(n * log(n))
        using polynom = ModintPolynomial<Mint>;
        polynom p;
        if (n == 0) return {1};
        p.coefficients = stirlingFirstKindAll(n / 2);
        p *= p.taylorShift(-n/2);
        if (n & 1) p *= polynom({1 - n, 1});
        return p.coefficients;
    }
    inline vector<Mint> stirlingFirstKindFixedK(int n, int k) {
        // Computes Stirling numbers of the first kind s(N,k) for fixed k ≤ N ≤ n
        // s(n,k) = n! ⋅ [xⁿ] (ln(1/(1 - x)))ᵏ / k!
        // Time : O(n * log(n))
        // Space : O(n)
        if (k == 0) {
            vector res(n + 1, Mint(0));
            res[0] = Mint(1);
            return res;
        }
        using polynom = ModintPolynomial<Mint>;
        vector<Mint> coeffs(n + 1);
        for (int i = 1; i <= n; i++)
            coeffs[i] = (i & 1 ? Mint(i).inv() : -Mint(i).inv());
        return (Factorial<Mint>::ifact(k) * polynom(coeffs).pow(k, n + 1).invborel().shiftLeft(k)).truncate(n + 1 - k).coefficients;
    }
    inline vector<Mint> stirlingSecondKindAll(int n) {
        // Computes Stirling numbers of the second kind S(n,k) for all 0 ≤ k ≤ n
        // ∑ₖ S(n,k) xᵏ = e⁻ˣ ⋅ ∑ᵢ (∑_{d|i} μ(d) ⋅ iⁿ/d) ⋅ xⁱ/i!
        // Time : O(n * log(n))
        // Space : O(n)
        using polynom = ModintPolynomial<Mint>;
        vector<Mint> coeffs(n + 2);
        coeffs[0] = n == 0 ? 1 : 0;
        coeffs[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (coeffs[i] == 0) {
                coeffs[i] = Mint(i).pow(n);
                for (int j = 2; i * j <= n; j++)
                    coeffs[i*j] = coeffs[i] * coeffs[j];
            }
        }
        vector<Mint> a(n + 1, 1);
        return (polynom(a).borel().mulx(-1) * polynom(coeffs).borel()).truncate(n + 1).coefficients;
    }
    inline vector<Mint> stirlingSecondKindFixedK(int n, int k) {
        // Computes Stirling numbers of the second kind S(N,k) for fixed k ≤ N ≤ n
        // S(n,k) = n! ⋅ [xⁿ] (eˣ - 1)ᵏ / k!
        // Time : O(n * log(n))
        // Space : O(n)
        if (k == 0) {
            vector res(n + 1, Mint(0));
            res[0] = Mint(1);
            return res;
        }
        using polynom = ModintPolynomial<Mint>;
        vector<Mint> a(n + 1, 1);
        a[0] = 0;
        return (Factorial<Mint>::ifact(k) * polynom(a).borel().pow(k, n + 1).invborel().shiftLeft(k)).truncate(n + 1 - k).coefficients;
    }

    inline vector<Mint> subFactorial(int n) {
        // Computes subfactorials !n for 0 ≤ k ≤ n
        // !n = (n - 1) ⋅ (!(n-1) + !(n-2)) with !0 = 1, !1 = 0
        // Time : O(n)
        // Space : O(n)
        vector<Mint> res(n + 1);
        res[0] = 1;
        for (int i = 2; i <= n; i++)
            res[i] = Mint(i - 1) * (res[i - 1] + res[i - 2]);
        return res;
    }

    inline vector<Mint> bellNumber(int n) {
        // Computes the number of ways to partition a set of n elements into non-empty subsets (Bell numbers Bₙ) for 0 ≤ k ≤ n
        // exp(eˣ - 1) = ∑ₙ Bₙ xⁿ/n!
        // Time : O(n * log(n))
        // Space : O(n)
        using polynom = ModintPolynomial<Mint>;
        vector<Mint> a(n + 1, 1);
        a[0] = 0;
        return polynom(a).borel().exp(n + 1).invborel().coefficients;
    }

    inline vector<Mint> bernoulliNumber(int n) {
        // Computes Bernoulli numbers Bₙ for 0 ≤ k ≤ n
        // x/(eˣ - 1) = ∑ₙ Bₙ xⁿ/n!
        // Time : O(n log n)
        // Space : O(n)
        using polynom = ModintPolynomial<Mint>;
        vector<Mint> a(n + 2, 1);
        a[0] = 0;
        return polynom(a).borel().shiftLeft(1).inverse(n + 1).invborel().coefficients;
    }
} // namespace Sequences