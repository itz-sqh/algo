#pragma once
#include <iostream>
template<long long MOD>
struct Modint
{
    long long x;
    constexpr Modint(long long v = 0) : x(v% MOD + (v >= 0 ? 0 : MOD)) {}
    constexpr Modint operator-() const { return x ? MOD - x : 0; }
    constexpr Modint operator+(const Modint& rhs) const { return Modint(*this) += rhs; }
    constexpr Modint operator-(const Modint& rhs) const { return Modint(*this) -= rhs; }
    constexpr Modint operator*(const Modint& rhs) const { return Modint(*this) *= rhs; }
    constexpr Modint operator/(const Modint& rhs) const { return Modint(*this) /= rhs; }
    constexpr Modint operator+=(const Modint& rhs) { x += rhs.x; if (x >= MOD) x -= MOD; return *this; }
    constexpr Modint operator-=(const Modint& rhs) { x -= rhs.x; if (x < 0) x += MOD; return *this; }
    constexpr Modint operator*=(const Modint& rhs) { (x *= rhs.x) %= MOD; return *this; }
    constexpr Modint operator/=(const Modint& rhs) { return *this *= pow(rhs, -1); }
    constexpr Modint operator==(const Modint& rhs) const { return x == rhs.x; }
    constexpr Modint operator!=(const Modint& rhs) const { return x != rhs.x; }
    constexpr long long rem() const { return 2 * x > MOD ? x - MOD : x; }
    constexpr Modint pow(long long p) const { return pow(*this, p); }
    constexpr Modint inv() const { return pow(x, -1); }
    template<class T> constexpr explicit operator T() const { return x; }
    constexpr static Modint pow(Modint a, long long p)
    {
        p = p % (MOD - 1) + (p >= 0 ? 0 : MOD - 1);
        Modint res = 1;
        while (p) { if (p & 1) res *= a; a *= a; p >>= 1; }
        return res;
    }
    constexpr void from_stream(std::istream& st) { st >> x; }
    constexpr void to_stream(std::ostream& st) const { st << x; }
};
template<long long MOD, class T> constexpr Modint<MOD> operator+(T a, Modint<MOD> b) { return static_cast<Modint<MOD>>(a) + b; }
template<long long MOD, class T> constexpr Modint<MOD> operator-(T a, Modint<MOD> b) { return static_cast<Modint<MOD>>(a) - b; }
template<long long MOD, class T> constexpr Modint<MOD> operator*(T a, Modint<MOD> b) { return static_cast<Modint<MOD>>(a) * b; }
template<long long MOD, class T> constexpr Modint<MOD> operator/(T a, Modint<MOD> b) { return static_cast<Modint<MOD>>(a) / b; }
template<long long MOD> constexpr std::istream& operator>>(std::istream& st, Modint<MOD>& a) { a.from_stream(st); return st; }
template<long long MOD> constexpr std::ostream& operator<<(std::ostream& st, const Modint<MOD>& a) { a.to_stream(st); return st; }