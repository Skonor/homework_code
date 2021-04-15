#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Polynomial {
private:
    vector<T> coefficients;

    void DeleteTrailingZeros(vector<T>& cfs) {
        size_t i = cfs.size();
        while (i > 0 && cfs[i - 1] == T(0)) {
            --i;
        }
        cfs.resize(i);
        if (cfs.size() == 0) {
            cfs.push_back(T(0));
        }
    }

public:
    Polynomial(const vector<T>& cfs) {
        coefficients = cfs;
        DeleteTrailingZeros(coefficients);
    }

    Polynomial(const T& cf = T(0)) {
        coefficients.push_back(cf);
    }

    template<typename ForwardIt>
    Polynomial(ForwardIt first, ForwardIt last) {
        for (auto it = first; it != last; ++it) {
            coefficients.push_back(*it);
        }
        DeleteTrailingZeros(coefficients);
    }

    friend bool operator == (const Polynomial<T>& p, const Polynomial<T>& q) {
        return p.coefficients == q.coefficients;
    }

    friend bool operator != (const Polynomial<T>& p, const Polynomial<T>& q) {
        return !(p == q);
    }

    int Degree() const {
        if (coefficients.size() == 1 && coefficients[0] == T(0)) {
            return -1;
        }
        return coefficients.size() - 1;
    }

    T operator[] (size_t i) const {
        if (i >= coefficients.size()) {
            return T(0);
        }
        return coefficients[i];
    }

    Polynomial<T>& operator += (const Polynomial<T>& other) {
        size_t new_size = max(coefficients.size(), other.coefficients.size());
        coefficients.resize(new_size);
        for (size_t i = 0; i < new_size; ++i) {
            coefficients[i] += other[i];
        }
        DeleteTrailingZeros(coefficients);
        return (*this);
    }

    Polynomial<T>& operator -= (const Polynomial<T>& other) {
        size_t new_size = max(coefficients.size(), other.coefficients.size());
        coefficients.resize(new_size);
        for (size_t i = 0; i < new_size; ++i) {
            coefficients[i] -= other[i];
        }
        DeleteTrailingZeros(coefficients);
        return (*this);
    }

    friend Polynomial<T> operator + (const Polynomial<T>& p, const Polynomial<T>& q) {
        auto result = p;
        result += q;
        return result;
    }

    friend Polynomial<T> operator - (const Polynomial<T>& p, const Polynomial<T>& q) {
        auto result = p;
        result -= q;
        return result;
    }

    Polynomial<T>& operator *= (const Polynomial<T>& p) {
        size_t new_deg = p.coefficients.size() + (*this).coefficients.size() - 2;
        vector<T> result(new_deg + 1);
        for (size_t i = 0; i <= new_deg; ++i) {
            for (size_t j = 0; j <= i; ++j) {
                result[i] += p[j] * (*this)[i - j];
            }
        }
        DeleteTrailingZeros(result);
        *this = Polynomial(result);
        return *this;
    }

    friend Polynomial<T> operator * (const Polynomial<T>& p, const Polynomial<T>& q) {
        auto result = p;
        result *= q;
        return result;
    }

    friend Polynomial<T> operator & (const Polynomial<T>& p, const Polynomial<T>& q) {
        Polynomial<T> result;
        Polynomial<T> subst(T(1));
        for (int i = 0; i <= p.Degree(); ++i) {
            result += p[i] * subst;
            subst *= q;
        }
        return result;
    }

    T operator() (const T& point) const {
        T result = T(0);
        T x_degree = T(1);
        for (size_t i = 0; i < coefficients.size(); ++i) {
            result += coefficients[i] * x_degree;
            x_degree *= point;
        }
        return result;
    }

    typename vector<T>::const_iterator end() const {
        return coefficients.end();
    }

    typename vector<T>::const_iterator begin() const {
        return coefficients.begin();
    }
};

template <typename T>
ostream& operator << (ostream& out, const Polynomial<T>& p) {
    for (int i = p.Degree(); i > 0; --i) {
        if (p[i] == T(0)) {
            continue;
        }
        if (p[i] > T(0) && i != p.Degree()) {
            out << "+";
        }
        if (p[i] != T(1) && p[i] != T(-1)) {
            out << p[i] << "*";
        } else if (p[i] == T(-1)) {
            out << "-";
        }
        out << "x";
        if (i != 1) {
            out << "^" << i;
        }
    }
    if (p[0] > T(0) && p.Degree() != 0) {
        out << "+";
    }
    if (p[0] != T(0)) {
        out << p[0];
    }
    if (p.Degree() == -1) {
        out << T(0);
    }
    return out;
}
