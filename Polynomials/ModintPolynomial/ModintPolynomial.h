#pragma once
#include <iostream>
#include <vector>
#include "NumberTheory/Factorials/Factrorial.h"
#include "Polynomials/FFT/FFT.h"

template <typename Modint, typename ftype = double>
class ModintPolynomial {
private:
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

    ModintPolynomial truncate(size_t k) const {
        if (k >= coefficients.size())
            return *this;
        return ModintPolynomial(std::vector<Modint>(coefficients.begin(), coefficients.begin() + k));
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
    ModintPolynomial log(size_t n) { // calculate log p(x) mod x^n
        assert(coefficients[0] == Modint(1));
        return (derivative().truncate(n) * inverse(n)).integral().truncate(n);
    }
    ModintPolynomial exp(size_t n) const {
        if (empty())
            return ModintPolynomial(Modint(1));
        assert(coefficients[0] == Modint(0));

        ModintPolynomial res(Modint(1));
        for (size_t a = 1; a < n; a *= 2) {
            size_t sz = std::min(2 * a, n);
            ModintPolynomial C = truncate(sz) - res.log(sz);
            C[0] += Modint(1);
            res = (res * C).truncate(sz);
        }
        return res;
    }
    ModintPolynomial pow(size_t k, size_t n) const {
        // calculate f(x)^k mod x^n
        if (empty())
            return k ? *this : ModintPolynomial(Modint(1));
        if (k == 0)
            return ModintPolynomial(Modint(1)).truncate(n);

        size_t trail = trailing();

        if (trail > 0) {
            if (k >= (n + trail - 1) / trail) {
                return ModintPolynomial();
            }
            return shiftLeft(trail).pow(k, n - trail * k).shiftRight(trail * k);
        }

        Modint mu = coefficients[0].pow(k);
        Modint di = coefficients[0].inv();

        ModintPolynomial normalized;
        for (size_t i = 0; i < std::min(coefficients.size(), n); i++)
            normalized[i] = coefficients[i] * di;

        ModintPolynomial log = normalized.log(n) * Modint(k);
        ModintPolynomial exp = log.exp(n);

        ModintPolynomial res;
        for (size_t i = 0; i < exp.size() && i < n; i++) {
            res[i] = exp[i] * mu;
        }

        return res.truncate(n);
    }

    ModintPolynomial inverse(size_t n) const {
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
    [[nodiscard]] size_t trailing() const { // p(x) = x^k*t(x), return k
        if (empty())
            return -1;
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
        // component-wise multiplication with a^k
        Modint cur = 1;
        ModintPolynomial res(*this);
        for (int i = 0; i <= deg(); i++) {
            res.coefficients[i] *= cur;
            cur *= a;
        }
        return res;
    }
    static ModintPolynomial ones(size_t n) { return ModintPolynomial(std::vector<Modint>(n, Modint(1))); }
    static ModintPolynomial expx(size_t n) { return ones(n).borel(); }

    ModintPolynomial taylorShift(Modint a) const {
        return (expx(deg() + 1).mulx(a).reverse() * invborel()).shiftLeft(deg()).borel();
    }

    bool operator==(const ModintPolynomial& other) const { return coefficients == other.coefficients; }

    bool operator!=(const ModintPolynomial& other) const { return coefficients != other.coefficients; }
};
