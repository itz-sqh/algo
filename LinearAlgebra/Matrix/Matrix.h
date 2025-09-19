#pragma once
#include <cassert>
#include <vector>
#include <iostream>
#include <limits>
#include <cmath>
#include <cstdint>

template <typename mtype = float>
struct Matrix {

    size_t n,m;
    std::vector<std::vector<mtype>> data;

    constexpr Matrix();
    constexpr Matrix(size_t n, size_t m, bool identity = false);
    constexpr Matrix(const std::vector<mtype>& vec, bool transpose = false);
    constexpr Matrix(std::initializer_list<std::initializer_list<mtype>> init);

    constexpr Matrix operator+=(const Matrix& other);
    constexpr Matrix operator+(const Matrix& other) const;

    constexpr Matrix operator-=(const Matrix& other);
    constexpr Matrix operator-(const Matrix& other) const;

    constexpr Matrix operator*=(const Matrix& other);
    constexpr Matrix operator*(const Matrix& other) const;

    constexpr Matrix operator*(const std::vector<mtype>& vec) const;
    constexpr Matrix operator*=(const std::vector<mtype>& vec);

    constexpr Matrix operator*=(mtype val);
    constexpr Matrix operator*(mtype val) const;

    constexpr Matrix operator/=(mtype val);
    constexpr Matrix operator/(mtype val) const;

    constexpr friend Matrix operator*(mtype val, const Matrix& mat) {
        return mat * val;
    }

    constexpr Matrix operator|(const Matrix& other) const;

    constexpr std::vector<mtype>& operator[] (size_t i);
    constexpr const std::vector<mtype>& operator[] (size_t i) const;

    constexpr bool operator==(const Matrix& other) const;
    constexpr bool operator!=(const Matrix& other) const;

    constexpr mtype& at(size_t i, size_t j);
    constexpr const mtype& at(size_t i, size_t j) const;

    constexpr Matrix row(size_t r) const;
    constexpr Matrix col(size_t c) const;
    constexpr Matrix subMatrix(size_t r1, size_t c1, size_t r2, size_t c2) const;

    constexpr void resize(size_t n, size_t m);

    constexpr Matrix transpose() const;

    constexpr void fill(mtype val);

    constexpr void to_stream(std::ostream& os) const {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                os << data[i][j] << " ";
            }
            os << "\n";
        }
    }
    constexpr void from_stream(std::istream& st) {
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                st >> data[i][j];
    }

    constexpr Matrix pow(std::uint64_t power) const {
        assert(n == m && "Matrix must be square for Matrix::pow");
        Matrix res = Matrix(n, n, true);
        Matrix A = *this;
        while (power) {
            if (power & 1)
                res *= A;
            A *= A;
            power >>= 1;
        }
        return res;
    }

    constexpr mtype det() const;
    [[nodiscard]] constexpr size_t rank() const;
    constexpr std::pair<mtype, Matrix> inv() const;
    constexpr std::pair<size_t, std::vector<mtype>> solve() const;

private:
    constexpr void normalize(size_t row);
    constexpr void eliminate(size_t col, bool upwards);
    constexpr auto classifyVariables(size_t lim) const;
    constexpr Matrix& gauss();
    constexpr Matrix& gaussJordan();
    constexpr bool isZero(mtype v) const {
        if constexpr (std::is_floating_point_v<mtype>) return std::abs(v) <= std::numeric_limits<mtype>::epsilon();
        else return v == mtype(0);
    }
};


template<typename mtype>
constexpr Matrix<mtype>::Matrix() : n(0), m(0) {}


template<typename mtype>
constexpr Matrix<mtype>::Matrix(size_t n, size_t m, const bool identity) : n(n),m(m), data(n,std::vector<mtype>(m,0)) {
    if (identity) {
        assert(!(identity && n!=m) && "Identity Matrix must be a square Matrix");
        for (size_t i = 0; i < n; ++i) {
            data[i][i] = 1;
        }
    }
}

template <typename mtype>
constexpr Matrix<mtype>::Matrix(const std::vector<mtype>& vec, const bool transpose)
    : n(transpose ? vec.size() : 1), m(transpose ? 1 : vec.size()) {

    if (transpose) {
        data.resize(vec.size());
        for (size_t i = 0; i < vec.size(); ++i)
            data[i] = {vec[i]};
    }
    else {
        data.resize(1);
        data[0] = vec;
    }
}


template<typename mtype>
constexpr Matrix<mtype>::Matrix(std::initializer_list<std::initializer_list<mtype>> init) : n(init.size()), m(init.begin()->size()), data(n,std::vector<mtype>(m)) {
    size_t i = 0;
    for (const auto& row : init) {
        assert(row.size() == m && "All rows must be the same size");
        size_t j = 0;
        for (const auto& x : row) {
            data[i][j] = x;
            ++j;
        }
        ++i;
    }
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator+=(const Matrix &other) {
    assert(n == other.n && m == other.m && "Matrices must be the same size");
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            data[i][j] += other.data[i][j];
        }
    }
    return *this;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator+(const Matrix& other) const {
    return Matrix(*this) += other;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator-=(const Matrix& other) {
    assert(n == other.n && m == other.m && "Matrices must be the same size");
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            data[i][j] -= other.data[i][j];
        }
    }
    return *this;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator-(const Matrix& other) const {
    return Matrix(*this) -= other;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator*=(const Matrix& other) {
    *this = *this * other;
    return *this;
}
template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator*(const Matrix& other) const {
    assert(m == other.n && "Inner sizes must be equal");
    Matrix res(n,other.m);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < other.m; ++j)
            for (size_t k = 0; k < m; k++)
                res[i][j] += data[i][k] * other.data[k][j];
    return res;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator*(const std::vector<mtype>& vec) const {
    assert(m == vec.size() && "Matrix columns must match vector size");

    Matrix res(n,1);

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            res[i][0] += data[i][j] * vec[j];
    return res;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator*=(const std::vector<mtype>& vec) {
    *this = *this * vec;
    return *this;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator*(mtype val) const {
    Matrix res(n,m);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            res[i][j] = data[i][j] * val;
    return res;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator*=(mtype val) {
    *this = *this * val;
    return *this;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator/(mtype val) const {
    assert(val != 0 && "Division by zero");
    Matrix res(n, m);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            res[i][j] = data[i][j] / val;
    return res;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator/=(mtype val) {
    assert(val != 0 && "Division by zero");
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            data[i][j] /= val;
    return *this;
}
template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::operator|(const Matrix& other) const {
    assert(n == other.n && "Matrices must have the same number of rows");
    Matrix res(n, m + other.m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            res[i][j] = data[i][j];
        for (size_t j = 0; j < other.m; ++j)
            res[i][m + j] = other.data[i][j];
    }
    return res;
}

template<typename mtype>
constexpr std::vector<mtype>& Matrix<mtype>::operator[] (size_t i) {
    assert(i < n && "Index out of bounds");
    return data[i];
}

template<typename mtype>
constexpr const std::vector<mtype>& Matrix<mtype>::operator[] (size_t i) const {
    assert(i < n && "Index out of bounds");
    return data[i];
}

template<typename mtype>
constexpr bool Matrix<mtype>::operator==(const Matrix& other) const {
    if (n != other.n || m != other.m) return false;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (data[i][j] != other.data[i][j]) return false;
        }
    }
    return true;
}

template<typename mtype>
constexpr bool Matrix<mtype>::operator!=(const Matrix& other) const {
    return !(*this == other);
}

template<typename mtype>
constexpr mtype& Matrix<mtype>::at(size_t i, size_t j) {
    assert(i<n && j < m && "Index out of bounds");
    return data[i][j];
}

template<typename mtype>
constexpr const mtype& Matrix<mtype>::at(size_t i, size_t j) const {
    assert(i<n && j < m && "Index out of bounds");
    return data[i][j];
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::row(size_t r) const {
    assert(r < n && "Row index out of bounds");
    Matrix res(1,m);
    for (size_t i = 0; i < m; ++i)
        res[0][i] = data[r][i];
    return res;
}


template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::col(size_t c) const {
    assert(c < m && "Column index out of bounds");
    Matrix res(n, 1);
    for (size_t i = 0; i < n; ++i)
        res[i][0] = data[i][c];
    return res;
}

template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::subMatrix(const size_t r1, const size_t c1, const size_t r2, const size_t c2) const {
    assert(r2 < n && c2 < m && r1 <= r2 && c1 <= c2);
    Matrix res(r2 - r1 + 1, c2 - c1 + 1);
    for (size_t i = r1; i <= r2; ++i)
        for (size_t j = c1; j <= c2; ++j)
            res.data[i - r1][j - c1] = data[i][j];
    return res;
}

template <typename mtype>
constexpr void Matrix<mtype>::resize(size_t n, size_t m) {
    data.resize(n);
    for (auto& it : data)
        it.resize(m);
}


template<typename mtype>
constexpr Matrix<mtype> Matrix<mtype>::transpose() const {
    Matrix res(m,n);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            res.data[j][i] = data[i][j];
    return res;
}

template<typename mtype>
constexpr void Matrix<mtype>::fill(mtype val) {
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            data[i][j] = val;
}

template<typename mtype>
constexpr void Matrix<mtype>::normalize(size_t row) {
    mtype div = data[row][row];
    for(size_t j = row; j < m; j++)
        data[row][j] /= div;
}

template<typename mtype>
constexpr void Matrix<mtype>::eliminate(size_t col, bool upwards) {
    size_t start = upwards ? 0 : col + 1;
    size_t end = upwards ? col : n;
    for(size_t i = start; i < end; i++) {
        if(i == col) continue;
        mtype factor = data[i][col];
        for(size_t j = col; j < m; j++)
            data[i][j] -= factor * data[col][j];
    }
}


template<typename mtype>
constexpr Matrix<mtype>& Matrix<mtype>::gauss() {
    for(size_t i = 0; i < n; i++) {
        size_t p = n;
        for (size_t j = i; j < n; j++)
            if (!isZero(data[j][i])) {
                p = j;
                break;
            }
        if(p == n) continue;
        if(p != i) std::swap(data[i], data[p]);
        normalize(i);
        eliminate(i, false);
    }
    return *this;
}

template<typename mtype>
constexpr Matrix<mtype>& Matrix<mtype>::gaussJordan() {
    // [A | E] -> [E | A^-1]
    gauss();
    for(int i = n-1; i >= 0; i--) {
        if(isZeroRow((*this)[i])) continue;
        eliminate(i, true);
    }
    return *this;
}

template<typename mtype>
constexpr auto Matrix<mtype>::classifyVariables(size_t lim) const {
    std::vector<size_t> pivots, free;
    size_t row = 0;
    for(size_t i = 0; i < lim; ++i) {
        if(row < n && !isZero(data[row][i])) {
            pivots.push_back(i);
            ++row;
        }
        else free.push_back(i);
    }
    return std::make_pair(pivots, free);
}

template<typename mtype>
constexpr mtype Matrix<mtype>::det() const {
    assert(n == m && "Matrix must be a square in order to use Matrix::det");
    Matrix tmp = *this;
    tmp.gauss();
    mtype res = 1;
    for(size_t i = 0; i < n; i++) res *= tmp[i][i];
    return res;
}

template<typename mtype>
constexpr size_t Matrix<mtype>::rank() const {
    Matrix tmp = *this;
    tmp.gauss();
    size_t rank = 0;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (!isZero(tmp[i][j])) {
                rank++; break;
            }
    return rank;
}

template<typename mtype>
constexpr std::pair<mtype, Matrix<mtype>> Matrix<mtype>::inv() const {
    assert(n == m && "Matrix must be a square in order to use Matrix::inv");
    Matrix tmp = *this | Matrix(n,n,true);
    tmp.gaussJordan();
    return {tmp.det(), tmp.subMatrix(0, n, n - 1, 2 * n - 1)};
}

template<typename mtype>
constexpr std::pair<size_t, std::vector<mtype>> Matrix<mtype>::solve() const {
    // TODO return basis
    Matrix tmp = *this;
    tmp.gauss();
    auto [pivots, free] = tmp.classifyVariables(m-1);

    for(size_t i = pivots.size(); i < n; ++i)
        if(!isZero(tmp[i][m-1]))
            return {0, {}};
    std::vector<mtype> res(m-1, mtype(0));
    for(int i = static_cast<int>(pivots.size()) -1; i >= 0; --i) {
        size_t col = pivots[i];
        res[col] = tmp[i][m-1];
        for(size_t j = col + 1; j < m-1; ++j) {
            res[col] -= tmp[i][j] * res[j];
        }
        res[col] /= tmp[i][col];
    }

    return {free.empty() ? 1 : 2, res};
}


template<typename mtype>
constexpr std::ostream& operator<<(std::ostream& st, const Matrix<mtype>& m) {
    m.to_stream(st);
    return st;
}

template<typename mtype>
constexpr std::istream& operator>>(std::istream& st, Matrix<mtype>& m) {
    m.from_stream(st);
    return st;
}




