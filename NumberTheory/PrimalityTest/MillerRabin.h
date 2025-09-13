#pragma once
#include "Utils/Binpow.h"

namespace MillerRabin {

    static bool checkComposite(unsigned long long n, unsigned long long a, unsigned long long d, int s) {
        long long x = binpow(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        for (int r = 0; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1)
                return false;
        }
        // definitely composite for this witness
        return true;
    }

    // Deterministic for all 64-bit integers
    // Determines if a number is prime in O(k * log^2(n)), k - number of bases
    static bool isPrime(unsigned long long n) {
        if (n < 2)
            return false;
        static constexpr unsigned long long smallPrimes[] = {2ULL,  3ULL,  5ULL,  7ULL,  11ULL, 13ULL,
                                                             17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL};
        for (unsigned long long p: smallPrimes)
            if (n % p == 0)
                return n == p;
        // n - 1 = d * 2 ^ s
        unsigned long long d = n - 1;
        int s = 0;
        while ((d & 1) == 0) {
            d >>= 1;
            ++s;
        }

        static constexpr unsigned long long bases[] = {2ULL,      325ULL,     9375ULL,      28178ULL,
                                                       450775ULL, 9780504ULL, 1795265022ULL};
        for (unsigned long long a: bases) {
            if (a % n == 0)
                continue;
            if (checkComposite(n, a, d, s)) // composite for this witness
                return false;
        }
        return true;
    }
}; // namespace MillerRabin
