#pragma once

constexpr long long exgcd(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    long long x1,y1;
    long long g = exgcd(b % a, a, x1, y1);
    x = y1 - b / a * x1;
    y = x1;
    return g;
}

long long exgcd(long long a, long long b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}
