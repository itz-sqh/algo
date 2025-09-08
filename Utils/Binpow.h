#pragma once

static long long mulmod(long long a, long long b, long long mod) {
    return static_cast<__uint128_t>(a) * b % mod;
}

inline long long binpow(long long a, long long n, long long mod) {
    long long res = 1;
    a %= mod;
    while (n) {
        if (n & 1)
            res = mulmod(res, a, mod);
        a = mulmod(a, a, mod);
        n >>= 1;
    }
    return res;
}