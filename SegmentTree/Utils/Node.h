#pragma once
#include <algorithm>
#include <climits>
#include <numeric>

using namespace std;

// Sum Query Node
struct SumNode {
    long long value;
    SumNode() : value(0) {}
    SumNode(long long val) : value(val) {}

    SumNode operator+(const SumNode& other) const { return SumNode(value + other.value); }
};

// Minimum Query Node
struct MinNode {
    long long value;
    MinNode() : value(LLONG_MAX) {}
    MinNode(long long val) : value(val) {}

    MinNode operator+(const MinNode& other) const { return MinNode(min(value, other.value)); }
};

// Maximum Query Node
struct MaxNode {
    long long value;
    MaxNode() : value(LLONG_MIN) {}
    MaxNode(long long val) : value(val) {}

    MaxNode operator+(const MaxNode& other) const { return MaxNode(max(value, other.value)); }
};

// GCD Node
struct GCDNode {
    long long value;
    GCDNode() : value(0) {}
    GCDNode(long long val) : value(val) {}

    GCDNode operator+(const GCDNode& other) const {
        if (value == 0)
            return other;
        if (other.value == 0)
            return *this;
        return GCDNode(gcd(value, other.value));
    }
};
