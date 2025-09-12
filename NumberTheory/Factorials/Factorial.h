#pragma once

#include <vector>
// UNTESTED !!!
template <typename Modint>
class Factorial {
private:
    static std::vector<Modint> fact_;
    static std::vector<Modint> ifact_;

public:
    static Modint fact(size_t n) {
        if (fact_.size() <= n) {
            size_t start = fact_.size();
            if (start == 0) {
                fact_.push_back(Modint(1));
                ifact_.push_back(Modint(1));
                start = 1;
            }

            fact_.resize(n + 1);
            ifact_.resize(n + 1);

            for (size_t i = start; i <= n; ++i) {
                fact_[i] = fact_[i-1] * Modint(i);
            }

            ifact_[n] = fact_[n].inv();
            for (size_t i = n; i > start; i--) {
                ifact_[i-1] = ifact_[i] * Modint(i);
            }
        }
        return fact_[n];
    }

    static Modint ifact(size_t n) {
        fact(n);
        return ifact_[n];
    }

};
template <typename Modint>
std::vector<Modint> Factorial<Modint>::fact_;

template <typename Modint>
std::vector<Modint> Factorial<Modint>::ifact_;
