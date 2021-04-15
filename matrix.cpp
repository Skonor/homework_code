#include <vector>
#include <utility>
#include <iostream>

using namespace std;

template<typename T>
class Matrix {
    vector<vector<T>> data;

public:
    Matrix(const vector<vector<T>> mat) {
        data = mat;
    }

    pair<size_t, size_t> size() const {
        if (data.size() == 0) {
            return make_pair(0, 0);
        }
        return make_pair(data.size(), data[0].size());
    }

    const vector<T>& operator[](size_t i) const {
        return data[i];
    }

    vector<T>& operator[](size_t i) {
        return data[i];
    }

    Matrix<T>& operator += (const Matrix<T>& other) {
        auto [m, n] = other.size();
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                data[i][j] += other[i][j];
            }
        }
        return *this;
    }

    template<typename D>
    Matrix<T>& operator *= (const D& scalar) {
        auto [m, n] = (*this).size();
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                data[i][j] *= scalar;
            }
        }
        return (*this);
    }

    template<typename D>
    Matrix<T> operator * (const D& scalar) const {
        Matrix<T> result = (*this);
        result *= scalar;
        return result;
    }

    Matrix<T>& transpose() {
        auto [m, n] = (*this).size();
        vector<vector<T>> result(n, vector<T>(m));
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result[j][i] = data[i][j];
            }
        }
        data = result;
        return *this;
    }

    Matrix<T> transposed() const {
        auto result = *this;
        return result.transpose();
    }

    Matrix<T> operator * (const Matrix& other) const {
        auto [m, n1] = (*this).size();
        auto [n2, r] = other.size();
        vector<vector<T>> result(m, vector<T>(r));
        for (size_t i = 0; i < m; ++i) {
            for (size_t k = 0; k < n1; ++k) {
                for (size_t j = 0; j < r; ++j) {
                    result[i][j] += data[i][k] * other[k][j];
                }
            }
        }
        return Matrix(result);
    }

    Matrix<T>& operator *= (const Matrix& other) {
        auto result = (*this) * other;
        (*this) = result;
        return *this;
    }
};

template<typename T>
ostream& operator << (ostream& out, const Matrix<T>& mat) {
    auto [m, n] = mat.size();
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            out << mat[i][j];
            if (j != n - 1) {
                out << "\t";
            }
        }
        if (i != m - 1) {
            out << "\n";
        }
    }
    return out;
}

template<typename T>
Matrix<T> operator + (const Matrix<T>& mat1, const Matrix<T>& mat2) {
    Matrix<T> result = mat1;
    result += mat2;
    return result;
}
