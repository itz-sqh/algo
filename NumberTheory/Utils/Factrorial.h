#pragma once

#include <vector>
using namespace std;
// UNTESTED !!!
template <typename Modint>
class Factorial {
private:
    static vector<Modint> fact_;
    static vector<Modint> ifact_;
    static constexpr size_t maxN = 1'000'000;
    static void init() {
        if (fact_.empty()) {
            fact_.reserve(maxN + 1);
            ifact_.reserve(maxN + 1);
            fact_.push_back(Modint(1));
            ifact_.push_back(Modint(1));
        }
    }

public:
    static Modint fact(size_t n) {
        init();
        if (fact_.size() <= n) {
            size_t start = fact_.size();
            fact_.resize(n + 1);
            ifact_.resize(n + 1);
            for (size_t i = start; i <= n; ++i)
                fact_[i] = fact_[i - 1] * Modint(i);
            ifact_[n] = fact_[n].inv();
            for (size_t i = n; i > start; --i)
                ifact_[i - 1] = ifact_[i] * Modint(i);
        }
        return fact_[n];
    }

    static Modint ifact(size_t n) {
        fact(n);
        return ifact_[n];
    }

};
template <typename Modint>
vector<Modint> Factorial<Modint>::fact_;

template <typename Modint>
vector<Modint> Factorial<Modint>::ifact_;
