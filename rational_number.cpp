#include <numeric>
#include <iostream>
#include <utility>

using namespace std;

class Rational {
    int numerator, denominator;

    void correction() {
        int d = gcd(numerator, denominator);
        numerator = numerator / d;
        denominator = denominator / d;
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
    }

public:
    Rational(int num = 0, int denom = 1) {
        numerator = num;
        denominator = denom;
        correction();
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

    Rational operator +() const {
        return Rational(numerator, denominator);
    }

    Rational operator -() const {
        return Rational(-numerator, denominator);
    }

    friend Rational operator + (const Rational& q1, const Rational& q2);

    friend Rational operator - (const Rational& q1, const Rational& q2);

    friend Rational operator * (const Rational& q1, const Rational& q2);

    friend Rational operator / (const Rational& q1, const Rational& q2);

    Rational& operator += (const Rational& q) {
        *this = *this + q;
        return *this;
    }

    Rational& operator -= (const Rational& q) {
        *this = *this - q;
        return *this;
    }

    Rational& operator *= (const Rational& q) {
        *this = *this * q;
        return *this;
    }

    Rational& operator /= (const Rational& q) {
        *this = *this / q;
        return *this;
    }

    Rational& operator ++() {
        *this = *this + 1;
        return *this;
    }

    Rational operator ++(int) {
        Rational copy(*this);
        ++*this;
        return copy;
    }

    Rational& operator --() {
        *this = *this - 1;
        return *this;
    }

    Rational operator --(int) {
        Rational copy(*this);
        --*this;
        return copy;
    }
};

Rational operator + (const Rational& q1, const Rational& q2) {
    return Rational(q1.Numerator() * q2.Denominator() + q1.Denominator() * q2.Numerator(),
                    q1.Denominator() * q2.Denominator());
}

Rational operator - (const Rational& q1, const Rational& q2) {
    return Rational(q1.Numerator() * q2.Denominator() - q1.Denominator() * q2.Numerator(),
                    q1.Denominator() * q2.Denominator());
}

Rational operator * (const Rational& q1, const Rational& q2) {
    return Rational(q1.Numerator() * q2.Numerator(),
                    q1.Denominator() * q2.Denominator());
}

Rational operator / (const Rational& q1, const Rational& q2) {
    return Rational(q1.Numerator() * q2.Denominator(),
                    q1.Denominator() * q2.Numerator());
}

bool operator == (const Rational& q1, const Rational& q2) {
    return q1.Numerator() == q2.Numerator() && q1.Denominator() == q2.Denominator();
}

bool operator != (const Rational& q1, const Rational& q2) {
    return q1.Numerator() != q2.Numerator() || q1.Denominator() != q2.Denominator();
}
