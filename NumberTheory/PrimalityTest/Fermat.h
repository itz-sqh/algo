#pragma once
#include "Utils/Binpow.h"
#include "Utils/Rng.h"
#include <numeric>
// UNTESTED !!!
struct Fermat {
    static bool isPrime(long long n, int iter = 100) {
        if (n < 4)
            return n == 2 || n == 3;
        for (int i = 0; i < iter; i++) {
            long long a = Rng::getLong(2, n - 2);
            if (std::gcd(a, n) != 1) return false;
            if (binpow(a, n - 1, n) != 1)
                return false;
        }
        return true;
    }
};