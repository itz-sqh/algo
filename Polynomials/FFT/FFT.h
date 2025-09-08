#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <complex>
#include <vector>
using namespace std;

// Implements fft using complex numbers
// Time : O(n * log(n))
// Space : O(n)

template <typename ftype>
struct FFT {
    static constexpr int maxn = 1 << 20;      // must be power of 2
    static constexpr int naiveThreshold = 50; // Threshold to use naive algorithm

    typedef complex<ftype> point;
    static constexpr ftype pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
    inline static point w[maxn];  // w[2^n + k] = exp(pi * k / (2^n))
    inline static int bitr[maxn]; // b[2^n + k] = bitreverse(k)
    inline static bool initiated;

    static void init() {
        if (!initiated) {
            for (int i = 1; i < maxn; i *= 2) {
                int ti = i / 2;
                for (int j = 0; j < i; j++) {
                    w[i + j] = polar(static_cast<ftype>(1), pi * j / i);
                    if (ti) {
                        bitr[i + j] = 2 * bitr[ti + j % ti] + (j >= ti);
                    }
                }
            }
            initiated = true;
        }
    }
    static void fft(vector<point>& a, int n) {
        init();
        if (n == 1) {
            return;
        }
        int hn = n / 2;
        for (int i = 0; i < n; i++) {
            int ti = 2 * bitr[hn + i % hn] + (i > hn);
            if (i < ti) {
                swap(a[i], a[ti]);
            }
        }
        for (int i = 1; i < n; i *= 2) {
            for (int j = 0; j < n; j += 2 * i) {
                for (int k = j; k < j + i; k++) {
                    point t = a[k + i] * w[i + k - j];
                    a[k + i] = a[k] - t;
                    a[k] += t;
                }
            }
        }
    }

    template <typename Mint>
    static void mulNaive(vector<Mint>& a, const vector<Mint>& b) {
        if (a.empty() || b.empty()) {
            a.clear();
            return;
        }

        int n = static_cast<int>(a.size());
        int m = static_cast<int>(b.size());
        a.resize(n + m - 1);

        for (int k = n + m - 2; k >= 0; --k) {
            a[k] *= b[0];
            for (int j = max(k - n + 1, 1); j < min(k + 1, m); ++j) {
                a[k] += a[k - j] * b[j];
            }
        }
    }
};

template <typename Mint, typename ftype>
struct DFT {
    typedef complex<ftype> point;
    static constexpr int split = 1 << 15; // ~ sqrt(mod)
    vector<point> A;

    DFT(const vector<Mint>& a, size_t n) : A(n) {
        for (size_t i = 0; i < min(n, a.size()); i++) {
            A[i] = point(a[i].rem() % split, a[i].rem() / split);
        }
        FFT<ftype>::fft(A, static_cast<int>(n));
    }

    vector<Mint> operator*(const DFT& B) const {
        assert(A.size() == B.A.size());
        size_t n = A.size();
        vector<point> C(n), D(n);

        for (size_t i = 0; i < n; i++) {
            C[i] = A[i] * (B[i] + conj(B[(n - i) % n]));
            D[i] = A[i] * (B[i] - conj(B[(n - i) % n]));
        }

        FFT<ftype>::fft(C, static_cast<int>(n));
        FFT<ftype>::fft(D, static_cast<int>(n));

        reverse(C.begin() + 1, C.end());
        reverse(D.begin() + 1, D.end());

        int t = 2 * static_cast<int>(n);
        vector<Mint> res(n);

        for (size_t i = 0; i < n; i++) {
            Mint A0 = llroundl(real(C[i]) / t);
            Mint A1 = llroundl(imag(C[i]) / t + imag(D[i]) / t);
            Mint A2 = llroundl(real(D[i]) / t);
            res[i] = A0 + A1 * split - A2 * split * split;
        }

        return res;
    }

    point& operator[](int i) { return A[i]; }
    point operator[](int i) const { return A[i]; }
};
namespace fft {
    inline size_t commonSize(size_t n, size_t m) {
        if (!n || !m) {
            return 0;
        }
        size_t k = n + m - 1;
        while (__builtin_popcount(k) != 1) {
            k++;
        }
        return k;
    }

    template <typename Mint, typename ftype>
    void mul(vector<Mint>& a, const vector<Mint>& b) {
        if (min(a.size(), b.size()) < FFT<ftype>::naiveThreshold) {
            FFT<ftype>::mulNaive(a, b);
            return;
        }

        size_t n = commonSize(a.size(), b.size());
        DFT<Mint, ftype> dftA(a, n);
        DFT<Mint, ftype> dftB(b, n);
        a = dftA * dftB;
    }
} // namespace fft
