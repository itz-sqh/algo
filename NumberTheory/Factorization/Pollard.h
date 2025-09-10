#pragma once
#include <algorithm>
#include <vector>
#include "Utils/Rng.h"
#include "NumberTheory/PrimalityTest/MillerRabin.h"
#include <numeric>

namespace Pollard {
    // Factors number n in O(n^1/4 * log(n)) and sorts all factors
    // Uses Floyd's cycle-finding algorithm
    static std::vector<std::pair<unsigned long long, int>> factorize(unsigned long long n, int iter = 70000) {
        if (n == 1) return {};
        if (MillerRabin::isPrime(n)) return {{n,1}};
        std::vector<std::pair<unsigned long long, int>> res;
        if (n % 2 == 0) {
            int power = 0;
            while (n % 2 == 0) {
                n /= 2;
                power++;
            }
            res.emplace_back(2, power);
            if (n > 1) {
                auto remaining = factorize(n);
                res.insert(res.end(), remaining.begin(), remaining.end());
            }
            return res;
        }
        auto f = [&](unsigned long long x, unsigned long long c) -> unsigned long long {
            return (static_cast<__uint128_t>(x) * x + c) % n;
        };
        while (true) {
            long long a = Rng::getLong(1ll, n - 3);
            long long b = a;
            long long c = Rng::getLong(1ll, n - 2);
            for (int i = 0; i < iter; i++) {
                a = f(a, c);
                b = f(f(b, c), c);
                long long g = std::gcd((a > b ? a - b : b - a), n);
                if (g != n && g != 1) {
                    auto factors1 = factorize(g);
                    auto factors2 = factorize(n / g);

                    res.reserve(factors1.size() + factors2.size());
                    res.insert(res.end(), factors1.begin(), factors1.end());
                    res.insert(res.end(), factors2.begin(), factors2.end());

                    std::sort(res.begin(), res.end());
                    std::vector<std::pair<unsigned long long, int>> merged;
                    for (auto &[factor, power] : res) {
                        if (merged.empty() || merged.back().first != factor) {
                            merged.emplace_back(factor, power);
                        } else {
                            merged.back().second += power;
                        }
                    }
                    return merged;
                }
            }
        }

    }
}; // namespace Pollard