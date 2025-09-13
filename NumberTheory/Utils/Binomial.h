#pragma once
#include "NumberTheory/Utils/Factorial.h"
#include "NumberTheory/Utils/Mint.h"

namespace Binomial {
    template<typename Modint = Mint>
    Modint C(int n, int k) {
        if (n - k < 0 || n < 0 || k < 0) return Modint(0);
        return Factorial<Modint>::fact(n) * Factorial<Modint>::ifact(k) * Factorial<Modint>::ifact(n - k);
    }
} // namespace Binomial