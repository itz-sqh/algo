#pragma once
#include <iostream>
#include <vector>
#include "NumberTheory/Utils/Factorial.h"
#include "Polynomials/FFT/FFT.h"

template <typename Modint, typename ftype = double>
class ModintPolynomial {
public:
    std::vector<Modint> coefficients;
    static constexpr int naiveThreshold = 50; // threshold to use naive algorithms

public:
    ModintPolynomial() = default;
    explicit ModintPolynomial(const std::vector<Modint>& coeffs) : coefficients(coeffs) {}
    ModintPolynomial(std::initializer_list<Modint> init) : coefficients(init) {}
    explicit ModintPolynomial(const Modint coeff) { coefficients.push_back(coeff); }

    void normalize() {
        while (!coefficients.empty() && coefficients.back() == Modint(0)) {
            coefficients.pop_back();
        }
    }
    [[nodiscard]] bool empty() const { return coefficients.empty(); }
    [[nodiscard]] int deg() const { return static_cast<int>(coefficients.size()) - 1; }
    [[nodiscard]] size_t size() const { return coefficients.size(); }
    Modint& operator[](size_t index) {
        if (index >= coefficients.size()) {
            coefficients.resize(index + 1, Modint(0));
        }
        return coefficients[index];
    }
    const Modint& operator[](size_t index) const {
        static Modint zero(0);
        return (index < coefficients.size()) ? coefficients[index] : zero;
    }

    auto begin() { return coefficients.begin(); }
    auto end() { return coefficients.end(); }
    auto begin() const { return coefficients.begin(); }
    auto end() const { return coefficients.end(); }

    ModintPolynomial operator-() const {
        auto res = *this;
        for (auto& coeff: res.coefficients) {
            coeff = -coeff;
        }
        return res;
    }

    ModintPolynomial& operator+=(const ModintPolynomial& other) {
        coefficients.resize(std::max(coefficients.size(), other.coefficients.size()), Modint(0));
        for (size_t i = 0; i < other.coefficients.size(); i++) {
            coefficients[i] += other.coefficients[i];
        }
        normalize();
        return *this;
    }

    ModintPolynomial& operator-=(const ModintPolynomial& other) {
        coefficients.resize(std::max(coefficients.size(), other.coefficients.size()), Modint(0));
        for (size_t i = 0; i < other.coefficients.size(); i++) {
            coefficients[i] -= other.coefficients[i];
        }
        normalize();
        return *this;
    }

    ModintPolynomial& operator*=(const ModintPolynomial& other) {
        if (empty() || other.empty()) {
            coefficients.clear();
            return *this;
        }
        fft::mul<Modint, ftype>(coefficients, other.coefficients);
        normalize();
        return *this;
    }

    ModintPolynomial& operator*=(Modint scalar) {
        for (auto& coeff: coefficients) {
            coeff *= scalar;
        }
        normalize();
        return *this;
    }
    ModintPolynomial& operator/=(Modint scalar) {
        Modint inv = scalar.inv();
        for (auto& coeff: coefficients) {
            coeff *= inv;
        }
        normalize();
        return *this;
    }

    ModintPolynomial operator+(const ModintPolynomial& other) const { return ModintPolynomial(*this) += other; }

    ModintPolynomial operator-(const ModintPolynomial& other) const { return ModintPolynomial(*this) -= other; }

    ModintPolynomial operator*(const ModintPolynomial& other) const { return ModintPolynomial(*this) *= other; }

    ModintPolynomial operator*(Modint scalar) const { return ModintPolynomial(*this) *= scalar; }

    ModintPolynomial operator/(Modint scalar) const { return ModintPolynomial(*this) /= scalar; }

    friend ModintPolynomial operator*(Modint scalar, const ModintPolynomial& poly) { return poly * scalar; }

    ModintPolynomial shiftRight(size_t k) const {
        if (empty())
            return *this;
        auto res = coefficients;
        res.insert(res.begin(), k, Modint(0));
        return ModintPolynomial(res);
    }

    ModintPolynomial shiftLeft(size_t k) const {
        if (k >= coefficients.size())
            return ModintPolynomial();
        return ModintPolynomial(std::vector<Modint>(coefficients.begin() + k, coefficients.end()));
    }

    ModintPolynomial substr(size_t l, size_t r) const {
        return ModintPolynomial(vector<Modint>(
            begin() + min(l, size()),
            begin() + min(r, size())
        ));
    }
    ModintPolynomial truncate(size_t k) const {
        return ModintPolynomial(std::vector<Modint>(coefficients.begin(), coefficients.begin() + min(k, coefficients.size())));
    }

    Modint evaluate(Modint x) const {
        Modint res(0);
        Modint power(1);
        for (const auto& coeff: coefficients) {
            res += coeff * power;
            power *= x;
        }
        return res;
    }

    vector<Modint> evaluate(const vector<Modint>& x) const {
        // https://cp-algorithms.com/algebra/polynomial.html#multi-point-evaluation
        // Time : O(n * log^2(n))
        // Space : O(n * log(n))
        int n = x.size();
        if (empty()) return vector<Modint>(n, 0);
        vector<ModintPolynomial> tree(4 * n);
        build(tree, x, 1, 0, n);
        vector<Modint> res(n);
        evaluate(tree, x, *this, res, 1, 0, n);
        return res;
    }
    void evaluate(const vector<ModintPolynomial>& tree, const vector<Modint>& x, const ModintPolynomial& poly, vector<Modint>& res,  int v, int l, int r) const {
        auto p = poly % tree[v];
        if (r - l <= naiveThreshold) {
            for (int i = l; i < r; i++) {
                res[i] = p.evaluate(x[i]);
            }
            return;
        }
        int mid = (l + r) / 2;
        evaluate(tree, x, p, res, 2 * v, l, mid);
        evaluate(tree, x, p, res, 2 * v + 1, mid, r);
    }

    static void build(vector<ModintPolynomial>& tree, const vector<Modint>& x, int v, int l, int r) {
        if (r - l == 1) {
            tree[v] = ModintPolynomial({-x[l], 1});
            return;
        }
        int m = (l + r) / 2;
        build(tree, x, 2 * v, l, m);
        build(tree, x, 2 * v + 1, m, r);
        tree[v] = tree[2 * v] * tree[2 * v + 1];
    }

    ModintPolynomial derivative(int k = 1) const {
        if (deg() + 1 < k)
            return ModintPolynomial(Modint(0));
        std::vector<Modint> res(deg() + 1 - k);
        for (int i = k; i <= deg(); i++) {
            res[i - k] = Factorial<Modint>::fact(i) * Factorial<Modint>::ifact(i - k) * coefficients[i];
        }
        return ModintPolynomial(res);
    }

    ModintPolynomial integral() const {
        if (empty())
            return ModintPolynomial();

        std::vector<Modint> res(coefficients.size() + 1);
        for (size_t i = 0; i < coefficients.size(); i++) {
            res[i + 1] = coefficients[i] * Modint(i + 1).inv();
        }
        return ModintPolynomial(res);
    }
    ModintPolynomial log(size_t n) const {
        // calculate log p(x) mod x^n
        // https://cp-algorithms.com/algebra/polynomial.html#logarithm
        assert(coefficients[0] == Modint(1));
        return (derivative().truncate(n) * inverse(n)).truncate(n-1).integral().truncate(n);
    }
    ModintPolynomial exp(size_t n) const {
        if (empty())
            return ModintPolynomial(Modint(1));
        assert(coefficients[0] == Modint(0));

        ModintPolynomial res(Modint(1));
        size_t a = 1;
        while (a < n) {
            ModintPolynomial c = res.log(2 * a).shiftLeft(a) - substr(a, 2 * a);
            res -= (res * c).truncate(a).shiftRight(a);
            a *= 2;
        }
        return res.truncate(n);
    }
    ModintPolynomial binpowNaive(size_t k, size_t n) const
    {
        // calculate f(x)^k mod x^n
        if (k == 0)
            return ModintPolynomial(Modint(1));
        if (empty())
            return ModintPolynomial(Modint(0));
        ModintPolynomial res(Modint(1));
        ModintPolynomial p = truncate(n);
        while (k)
        {
            if (k & 1)
                res = (res * p).truncate(n);
            p = (p * p).truncate(n);
            k >>= 1;
        }
        return res;
    }

    ModintPolynomial pow(size_t k, size_t n) const {
        // calculate f(x)^k mod x^n
        // https://cp-algorithms.com/algebra/polynomial.html#k-th-power
        if (empty())
            return k ? *this : ModintPolynomial(Modint(1));
        size_t trail = trailing();
        if (trail > 0)
            return k >= static_cast<long long>(n + trail - 1) / trail
                ? ModintPolynomial(Modint(0))
                : shiftLeft(trail).pow(k, n - trail * k).shiftRight(trail * k);
        if (k <= naiveThreshold)
            return binpowNaive(k, n);
        ModintPolynomial b; b.coefficients.resize(coefficients.size());
        int p = 0;
        while (k * p < static_cast<int>(coefficients.size()) && coefficients[p] == Modint(0)) p++;
        if (1ll * k * p >= static_cast<int>(coefficients.size())) return b;
        Modint mu = Modint::pow(coefficients[p], k), di = coefficients[p].inv();
        size_t m = k * p;
        ModintPolynomial c; c.coefficients.resize(n - m);
        for (int x = 0; x < n - m; x++) c.coefficients[x] = coefficients[x + p] * di;
        c = c.log(n - m);
        for (auto& x : c.coefficients) x *= k;
        c = c.exp(n - m);
        for (int x = 0; x < static_cast<int>(c.size()); x++) b.coefficients[x + m] = c.coefficients[x] * mu;
        return b;
    }

    ModintPolynomial inverse(size_t n) const {
        // https://cp-algorithms.com/algebra/polynomial.html#inverse-series_1
        assert(!empty());
        assert(coefficients[0] != Modint(0));

        if (n == 1)
            return ModintPolynomial(coefficients[0].inv());

        size_t k = (n + 1) / 2;
        ModintPolynomial B = inverse(k);

        ModintPolynomial QB = (truncate(n) * B).truncate(n);
        return (B * (ModintPolynomial({Modint(2)}) - QB)).truncate(n);
    }

    std::pair<ModintPolynomial, ModintPolynomial> divMod(const ModintPolynomial& divisor) const {
        assert(!divisor.empty());

        if (deg() < divisor.deg()) {
            return {ModintPolynomial(), *this};
        }

        if (std::min(deg(), divisor.deg()) < naiveThreshold) {
            return divModNaive(divisor);
        }

        int d = deg() - divisor.deg();
        ModintPolynomial D =
            (reverse().truncate(d + 1) * divisor.reverse().inverse(d + 1)).truncate(d + 1).reverse(d + 1);
        return {D, *this - D * divisor};
    }

    ModintPolynomial operator/(const ModintPolynomial& other) const { return divMod(other).first; }

    ModintPolynomial operator%(const ModintPolynomial& other) const { return divMod(other).second; }

    std::pair<ModintPolynomial, ModintPolynomial> divModNaive(const ModintPolynomial& divisor) const {
        std::vector<Modint> A = coefficients;
        std::vector<Modint> quotient;

        while (A.size() >= divisor.coefficients.size()) {
            Modint q = A.back() * divisor.coefficients.back().inv();
            quotient.push_back(q);

            if (q != Modint(0)) {
                for (size_t i = 0; i < divisor.coefficients.size(); i++) {
                    size_t idx = A.size() - i - 1;
                    A[idx] -= q * divisor.coefficients[divisor.coefficients.size() - i - 1];
                }
            }
            A.pop_back();
        }

        std::reverse(quotient.begin(), quotient.end());
        return {ModintPolynomial(quotient), ModintPolynomial(A)};
    }

    ModintPolynomial reverse(size_t n) const {
        std::vector<Modint> res(n, Modint(0));
        size_t mn = std::min(n, coefficients.size());
        for (size_t i = 0; i < mn; i++) {
            res[n - 1 - i] = coefficients[i];
        }
        return ModintPolynomial(res);
    }

    ModintPolynomial reverse() const { return reverse(coefficients.size()); }

    void print(size_t n) const {
        for (size_t i = 0; i < n; i++) {
            if (i < coefficients.size()) {
                std::cout << coefficients[i];
            }
            else {
                std::cout << Modint(0);
            }
            if (i < n - 1)
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
    [[nodiscard]] size_t trailing() const {
        // f(x) = x^k * p(x), return k
        if (empty())
            return 0;
        int res = 0;
        while (coefficients[res] == Modint(0) && res < coefficients.size())
            res++;
        return res;
    }

    ModintPolynomial borel() const {
        // ak /= k!
        auto res = *this;
        for (int i = 0; i <= deg(); i++)
            res.coefficients[i] *= Factorial<Modint>::ifact(i);
        return res;
    }
    ModintPolynomial invborel() const {
        // ak /= k!
        auto res = *this;
        for (int i = 0; i <= deg(); i++)
            res.coefficients[i] *= Factorial<Modint>::fact(i);
        return res;
    }
    ModintPolynomial mulx(Modint a) const {
        // f(ax)
        Modint cur = 1;
        ModintPolynomial res(*this);
        for (int i = 0; i <= deg(); i++) {
            res.coefficients[i] *= cur;
            cur *= a;
        }
        return res;
    }

    ModintPolynomial taylorShift(Modint a) const {
        vector<Modint> ones(deg() + 1, 1);
        return (ModintPolynomial(ones).borel().mulx(a).reverse() * invborel()).shiftLeft(deg()).borel();
    }

    bool operator==(const ModintPolynomial& other) const { return coefficients == other.coefficients; }

    bool operator!=(const ModintPolynomial& other) const { return coefficients != other.coefficients; }
};
