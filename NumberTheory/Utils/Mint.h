#pragma once
#include <iostream>
struct Mint
{
    static long long MOD;
    long long x;
    Mint(long long v = 0) : x(v% MOD + (v >= 0 ? 0 : MOD)) {}
    Mint operator+(const Mint& rhs) const { return Mint(*this) += rhs; }
    Mint operator-(const Mint& rhs) const { return Mint(*this) -= rhs; }
    Mint operator*(const Mint& rhs) const { return Mint(*this) *= rhs; }
    Mint operator/(const Mint& rhs) const { return Mint(*this) /= rhs; }
    Mint operator+=(const Mint& rhs) { x += rhs.x; if (x >= MOD) x -= MOD; return *this; }
    Mint operator-=(const Mint& rhs) { x -= rhs.x; if (x < 0) x += MOD; return *this; }
    Mint operator*=(const Mint& rhs) { (x *= rhs.x) %= MOD; return *this; }
    Mint operator/=(const Mint& rhs) { return *this *= pow(rhs, -1); }
    Mint operator==(const Mint& rhs) const { return x == rhs.x; }
    Mint operator!=(const Mint& rhs) const { return x != rhs.x; }
    long long rem() const { return 2 * x > MOD ? x - MOD : x; }
    Mint pow(long long p) const { return pow(*this, p); }
    Mint inv() const { return pow(x, -1); }
    static long long mod() { return MOD; }
    template<class T> constexpr explicit operator T() const { return x; }
    static Mint pow(Mint a, long long p)
    {
        p = p % (MOD - 1) + (p >= 0 ? 0 : MOD - 1);
        Mint res = 1;
        while (p) { if (p & 1) res *= a; a *= a; p >>= 1; }
        return res;
    }
    void from_stream(std::istream& st) { st >> x; }
    void to_stream(std::ostream& st) const { st << x; }
};
template<class T> Mint operator+(T a, Mint b) { return static_cast<Mint>(a) + b; }
template<class T> Mint operator-(T a, Mint b) { return static_cast<Mint>(a) - b; }
template<class T> Mint operator*(T a, Mint b) { return static_cast<Mint>(a) * b; }
template <class T> Mint operator/(T a, Mint b) { return static_cast<Mint>(a) / b; }
inline std::istream& operator>>(std::istream& st, Mint& a) { a.from_stream(st); return st; }
inline std::ostream& operator<<(std::ostream& st, const Mint& a) { a.to_stream(st); return st; }

long long Mint::MOD = 998244353;